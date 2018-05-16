/* isolator-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * spitfp_master.c: Implementation of SPI TF Protocol Master
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "spitfp_master.h"

#include "communication.h"

#include "configs/config_spitfp_master.h"

#include "bricklib2/logging/logging.h"

#include "bricklib2/utility/pearson_hash.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/protocols/spitfp/spitfp.h"

#define spitfp_master_rx_irq_handler IRQ_Hdlr_11
#define spitfp_master_tx_irq_handler IRQ_Hdlr_12

SPITFPMaster spitfp_master;

void __attribute__((optimize("-O3"))) __attribute__((section (".ram_code"))) spitfp_master_tx_irq_handler(void) {
	while(!XMC_USIC_CH_TXFIFO_IsFull(SPITFP_MASTER_USIC)) {
		if(spitfp_master.buffer_send_index < spitfp_master.buffer_send_length) {
			spitfp_master.counter_send++;
			SPITFP_MASTER_USIC->IN[0] = spitfp_master.buffer_send[spitfp_master.buffer_send_index];

			spitfp_master.buffer_send_index++;
			if(spitfp_master.buffer_send_index >= spitfp_master.buffer_send_length) {

				// We don't expect an ACK to be acked, so we can set the length to 0 here
				if(spitfp_master.buffer_send_length == SPITFP_PROTOCOL_OVERHEAD) {
					spitfp_master.buffer_send_length = 0;
					spitfp_master.buffer_send_index = 0;
				}
			}
		} else {
			spitfp_master.counter_send++;
			SPITFP_MASTER_USIC->IN[0] = 0;

			if(spitfp_master.zero_count_recv >= 2) {
				spitfp_master.zero_count_recv = 0;
				XMC_USIC_CH_TXFIFO_DisableEvent(SPITFP_MASTER_USIC, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);
				XMC_USIC_CH_TXFIFO_ClearEvent(SPITFP_MASTER_USIC, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);
			}
		}
	}
}

void __attribute__((optimize("-O3"))) __attribute__((section (".ram_code"))) spitfp_master_rx_irq_handler(void) {
	while(!XMC_USIC_CH_RXFIFO_IsEmpty(SPITFP_MASTER_USIC)) {
		const uint8_t data = SPITFP_MASTER_USIC->OUTR;
		ringbuffer_add(&spitfp_master.ringbuffer_recv, data);
		if(data == 0) {
			spitfp_master.zero_count_recv++;
		} else {
			spitfp_master.zero_count_recv = 0;
		}

		spitfp_master.counter_recv++;
		if(spitfp_master.counter_recv >= spitfp_master.counter_send) {
			spitfp_master.counter_send = 0;
			spitfp_master.counter_recv = 0;

			XMC_SPI_CH_DisableSlaveSelect(SPITFP_MASTER_USIC);
		}
	}

	/*
	while(!XMC_USIC_CH_RXFIFO_IsEmpty(SPITFP_MASTER_USIC)) {
		ringbuffer_recv_buffer[ringbuffer_recv->end] = SPITFP_MASTER_USIC->OUTR;
		ringbuffer_recv->end = (ringbuffer_recv->end + 1) & SPITFP_RECEIVE_BUFFER_MASK;

		// Without this "if" the interrupt takes 1.39us, including the "if" it takes 1.75us
		// Without the "if" it still works, but we loose the overflow counter,
		// we will get frame/checksum errors instead
#ifndef BOOTLOADER_XMC_RX_IRQ_NO_OVERFLOW
		// Tell GCC that this branch is unlikely to occur => __builtin_expect(value, 0)
		if(__builtin_expect((ringbuffer_recv->end == ringbuffer_recv->start), 0)) {
			bootloader_status.error_count.error_count_overflow++;
			ringbuffer_recv->end = (ringbuffer_recv->end - 1) & SPITFP_RECEIVE_BUFFER_MASK;
		}
#endif

	}*/
}


void spitfp_master_init_spi(void) {
	// USIC channel configuration
	const XMC_SPI_CH_CONFIG_t channel_config = {
		.baudrate       = 1000000,
		.bus_mode       = XMC_SPI_CH_BUS_MODE_MASTER,
		.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
		.parity_mode    = XMC_USIC_CH_PARITY_MODE_NONE
	};

	// MOSI pin configuration
	const XMC_GPIO_CONFIG_t mosi_pin_config = {
		.mode             = SPITFP_MASTER_MOSI_PIN_AF,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
	};

	// MISO pin configuration
	const XMC_GPIO_CONFIG_t miso_pin_config = {
		.mode             = XMC_GPIO_MODE_INPUT_TRISTATE,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
	};

	// SCLK pin configuration
	const XMC_GPIO_CONFIG_t sclk_pin_config = {
		.mode             = SPITFP_MASTER_SCLK_PIN_AF,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
	};

	// SELECT pin configuration
	const XMC_GPIO_CONFIG_t select_pin_config = {
		.mode             = SPITFP_MASTER_SELECT_PIN_AF,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
	};

	// Configure MISO pin
	XMC_GPIO_Init(SPITFP_MASTER_MISO_PIN, &miso_pin_config);

	// Initialize USIC channel in SPI master mode
	XMC_SPI_CH_Init(SPITFP_MASTER_USIC, &channel_config);
	SPITFP_MASTER_USIC->SCTR &= ~USIC_CH_SCTR_PDL_Msk; // Set passive data level to 0

	XMC_SPI_CH_SetBitOrderMsbFirst(SPITFP_MASTER_USIC);

	XMC_SPI_CH_SetWordLength(SPITFP_MASTER_USIC, (uint8_t)8U);
	XMC_SPI_CH_SetFrameLength(SPITFP_MASTER_USIC, (uint8_t)64U);

	XMC_SPI_CH_SetTransmitMode(SPITFP_MASTER_USIC, XMC_SPI_CH_MODE_STANDARD);

	// Configure the clock polarity and clock delay
	XMC_SPI_CH_ConfigureShiftClockOutput(SPITFP_MASTER_USIC,
									     XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_DISABLED,
									     XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);
	// Configure Leading/Trailing delay
	XMC_SPI_CH_SetSlaveSelectDelay(SPITFP_MASTER_USIC, 2);


	// Set input source path
	XMC_SPI_CH_SetInputSource(SPITFP_MASTER_USIC, SPITFP_MASTER_MISO_INPUT, SPITFP_MASTER_MISO_SOURCE);

	// SPI Mode: CPOL=1 and CPHA=1
	SPITFP_MASTER_USIC_CHANNEL->DX1CR |= USIC_CH_DX1CR_DPOL_Msk;

	// Configure transmit FIFO
	XMC_USIC_CH_TXFIFO_Configure(SPITFP_MASTER_USIC, SPITFP_MASTER_TX_DATA_POINTER, XMC_USIC_CH_FIFO_SIZE_16WORDS, SPITFP_MASTER_TX_LIMIT);

	// Configure receive FIFO
	XMC_USIC_CH_RXFIFO_Configure(SPITFP_MASTER_USIC, SPITFP_MASTER_RX_DATA_POINTER, XMC_USIC_CH_FIFO_SIZE_16WORDS, SPITFP_MASTER_RX_LIMIT);
//	SPITFP_MASTER_USIC->RBCTR |= USIC_CH_RBCTR_SRBTM_Msk; // RX Interrupt for >= 0

	// Set service request for tx FIFO transmit interrupt
	XMC_USIC_CH_TXFIFO_SetInterruptNodePointer(SPITFP_MASTER_USIC, XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD, SPITFP_MASTER_SERVICE_REQUEST_TX);  // IRQ SPITFP_MASTER_IRQ_TX

	// Set service request for rx FIFO receive interrupt
	XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(SPITFP_MASTER_USIC, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD, SPITFP_MASTER_SERVICE_REQUEST_RX);  // IRQ SPITFP_MASTER_IRQ_RX
	XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(SPITFP_MASTER_USIC, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE, SPITFP_MASTER_SERVICE_REQUEST_RX); // IRQ SPITFP_MASTER_IRQ_RX

	//Set priority and enable NVIC node for transmit interrupt
	NVIC_SetPriority(SPITFP_MASTER_IRQ_TX, SPITFP_MASTER_IRQ_TX_PRIORITY);
	NVIC_EnableIRQ(SPITFP_MASTER_IRQ_TX);

	// Set priority and enable NVIC node for receive interrupt
	NVIC_SetPriority(SPITFP_MASTER_IRQ_RX, SPITFP_MASTER_IRQ_RX_PRIORITY);
	NVIC_EnableIRQ(SPITFP_MASTER_IRQ_RX);

	// Start SPI
	XMC_SPI_CH_Start(SPITFP_MASTER_USIC);

	// Configure SCLK pin
	XMC_GPIO_Init(SPITFP_MASTER_SCLK_PIN, &sclk_pin_config);

	// Configure slave select pin
	XMC_GPIO_Init(SPITFP_MASTER_SELECT_PIN, &select_pin_config);

	//Configure MOSI pin
	XMC_GPIO_Init(SPITFP_MASTER_MOSI_PIN, &mosi_pin_config);

	XMC_USIC_CH_RXFIFO_EnableEvent(SPITFP_MASTER_USIC, XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD | XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE);

	XMC_SPI_CH_EnableSlaveSelect(SPITFP_MASTER_USIC, XMC_SPI_CH_SLAVE_SELECT_0);
	XMC_USIC_CH_TXFIFO_EnableEvent(SPITFP_MASTER_USIC, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);
	XMC_USIC_CH_TriggerServiceRequest(SPITFP_MASTER_USIC, SPITFP_MASTER_SERVICE_REQUEST_TX);
}

void spitfp_master_init(void) {
//	uartbb_printf("spitfp_master_init start\n\r");
	memset(&spitfp_master, 0, sizeof(SPITFPMaster));
	ringbuffer_init(&spitfp_master.ringbuffer_recv, SPITFP_MASTER_BUFFER_LENGTH, spitfp_master.buffer_recv);

    spitfp_master_init_spi();
//	uartbb_printf("spitfp_master_init end\n\r");
}

void spitfp_master_trigger_send(void) {
	XMC_SPI_CH_EnableSlaveSelect(SPITFP_MASTER_USIC, XMC_SPI_CH_SLAVE_SELECT_0);
	XMC_USIC_CH_TXFIFO_EnableEvent(SPITFP_MASTER_USIC, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);
	XMC_USIC_CH_TriggerServiceRequest(SPITFP_MASTER_USIC, SPITFP_MASTER_SERVICE_REQUEST_TX);
}

uint8_t spitfp_master_get_sequence_byte(const bool increase) {
	if(increase) {
		spitfp_master.current_sequence_number++;
		if(spitfp_master.current_sequence_number > 0xF) {
			spitfp_master.current_sequence_number = 2;
		}
	}

//	uartbb_printf("get seq byte: %d -> %d\n\r", increase, spitfp_master.current_sequence_number);

	return spitfp_master.current_sequence_number | (spitfp_master.last_sequence_number_seen << 4);
}

void spitfp_master_send_ack_and_message(uint8_t *data, const uint8_t length) {
//	uartbb_printf("send ack and message: %d\n\r", length);
	uint8_t checksum = 0;
	spitfp_master.buffer_send_length = length + SPITFP_PROTOCOL_OVERHEAD;
	spitfp_master.buffer_send[0] = spitfp_master.buffer_send_length;
	PEARSON(checksum, spitfp_master.buffer_send_length);

	spitfp_master.buffer_send[1] = spitfp_master_get_sequence_byte(true);
	PEARSON(checksum, spitfp_master.buffer_send[1]);

	for(uint8_t i = 0; i < length; i++) {
		spitfp_master.buffer_send[2+i] = data[i];
		PEARSON(checksum, spitfp_master.buffer_send[2+i]);
	}

	spitfp_master.buffer_send[length + SPITFP_PROTOCOL_OVERHEAD-1] = checksum;

	spitfp_master_trigger_send();
	spitfp_master.last_send_started = system_timer_get_ms();
}

void spitfp_master_send_ack(void) {
//	uartbb_printf("ack: %d\n\r", spitfp_master.buffer_message_from_brick_length);
	if(spitfp_master.buffer_message_from_brick_length > 0) {
		spitfp_master_send_ack_and_message(spitfp_master.buffer_message_from_brick, spitfp_master.buffer_message_from_brick_length);
		spitfp_master.buffer_message_from_brick_length = 0;
		return;
	}

	// Set new sequence number and checksum for ACK
	spitfp_master.buffer_send[0] = SPITFP_PROTOCOL_OVERHEAD;
	spitfp_master.buffer_send[1] = spitfp_master.last_sequence_number_seen << 4;
	spitfp_master.buffer_send[2] = pearson_permutation[pearson_permutation[spitfp_master.buffer_send[0]] ^ spitfp_master.buffer_send[1]];

	spitfp_master.buffer_send_length = SPITFP_PROTOCOL_OVERHEAD;

	spitfp_master_trigger_send();
	spitfp_master.last_send_started = system_timer_get_ms();
}

bool spitfp_master_is_send_possible(void) {
	 return spitfp_master.buffer_send_length == 0 && ((SPITFP_MASTER_USIC->PCR_SSCMode & USIC_CH_PCR_SSCMode_SELO_Msk) == 0);
}

void spitfp_master_check_message_send_timeout(void) {
	// If we are not currently sending a message
	// and there is still data in the buffer 
	// and the timeout ran out we resend the message
	if((spitfp_master.buffer_send_length > SPITFP_PROTOCOL_OVERHEAD) && 
       ((SPITFP_MASTER_USIC->PCR_SSCMode & USIC_CH_PCR_SSCMode_SELO_Msk) == 0) && 
	   system_timer_is_time_elapsed_ms(spitfp_master.last_send_started, /*SPITFP_TIMEOUT*/ 250)) {
		uartbb_printf("resend\n\r");

		spitfp_master.buffer_send_index = 0;
		spitfp_master_trigger_send();
		spitfp_master.last_send_started = system_timer_get_ms();
	}
}

void spitfp_master_handle_protocol_error(void) {
	// In case of error we completely empty the ringbuffer
	uint8_t data;
	while(ringbuffer_get(&spitfp_master.ringbuffer_recv, &data));
}

void spitfp_master_check(void) {
	// If the temporary buffer length is > 0 we still have a message to handle
	if(spitfp_master.buffer_recv_tmp_length > 0) {
		if(spitfp_master.buffer_send_length == 0 /*spitfp_master_is_send_possible()*/) {
			if(spitfp_master.buffer_recv_tmp_length == SPITFP_PROTOCOL_OVERHEAD) {
				// If the length is set to SPITFP_PROTOCOL_OVERHEAD we just have to answer with an ACK
				spitfp_master_send_ack();
				spitfp_master.buffer_recv_tmp_length = 0;
			} else {
				 if(communication_handle_message_from_bricklet(spitfp_master.buffer_recv_tmp, spitfp_master.buffer_recv_tmp_length)) {
					spitfp_master.buffer_recv_tmp_length = 0;
				 }
			}
		} else {
			uartbb_printf("send not possible: %d %d\n\r", spitfp_master.buffer_send_length, spitfp_master.buffer_send_index);
		}
	}

	spitfp_master_check_message_send_timeout();

	uint8_t message[TFP_MESSAGE_MAX_LENGTH] = {0};
	uint8_t message_position = 0;
	uint16_t num_to_remove_from_ringbuffer = 0;
	uint8_t checksum = 0;

	uint8_t data_sequence_number = 0;
	uint8_t data_length = 0;

	SPITFPState state = SPITFP_STATE_START;
	uint16_t used = ringbuffer_get_used(&spitfp_master.ringbuffer_recv);
	uint16_t start = spitfp_master.ringbuffer_recv.start;

	for(uint16_t i = start; i < start+used; i++) {
		const uint16_t index = i & SPITFP_RECEIVE_BUFFER_MASK;
		const uint8_t data = spitfp_master.buffer_recv[index];

		// Handle "standard case" first (we are sending data and Master has nothing to send)
		if(state == SPITFP_STATE_START && data == 0) {
			// equivalent (but faster) to "ringbuffer_remove(&spitfp_master.ringbuffer_recv, 1);"
			spitfp_master.ringbuffer_recv.start = (spitfp_master.ringbuffer_recv.start + 1) & SPITFP_RECEIVE_BUFFER_MASK;
			continue;
		}
		num_to_remove_from_ringbuffer++;

		switch(state) {
			case SPITFP_STATE_START: {
				checksum = 0;
				message_position = 0;

				if(data == SPITFP_PROTOCOL_OVERHEAD) {
					state = SPITFP_STATE_ACK_SEQUENCE_NUMBER;
				} else if(data >= SPITFP_MIN_TFP_MESSAGE_LENGTH && data <= SPITFP_MAX_TFP_MESSAGE_LENGTH) {
					state = SPITFP_STATE_MESSAGE_SEQUENCE_NUMBER;
				} else if(data == 0) {
					// equivalent (but faster) to "ringbuffer_remove(&spitfp_master.ringbuffer_recv, 1);"
					spitfp_master.ringbuffer_recv.start = (spitfp_master.ringbuffer_recv.start + 1) & SPITFP_RECEIVE_BUFFER_MASK;
					num_to_remove_from_ringbuffer--;
					break;
				} else {
					// If the length is not PROTOCOL_OVERHEAD or within [MIN_TFP_MESSAGE_LENGTH, MAX_TFP_MESSAGE_LENGTH]
					// or 0, something has gone wrong!
//					bootloader_status->error_count.error_count_frame++; // TODO
					loge("Error 1\n\r");
					spitfp_master_handle_protocol_error();
					return;
				}

				data_length = data;
				if((start+used - i) < data_length) {
					// There can't be enough data for a whole message, we can return here.
					return;
				}
				PEARSON(checksum, data_length);

				break;
			}

			case SPITFP_STATE_ACK_SEQUENCE_NUMBER: {
				data_sequence_number = data;
				PEARSON(checksum, data_sequence_number);
				state = SPITFP_STATE_ACK_CHECKSUM;
				break;
			}

			case SPITFP_STATE_ACK_CHECKSUM: {
				// Whatever happens here, we will go to start again and remove
				// data from ringbuffer
				state = SPITFP_STATE_START;
				ringbuffer_remove(&spitfp_master.ringbuffer_recv, num_to_remove_from_ringbuffer);
				num_to_remove_from_ringbuffer = 0;

				if(checksum != data) {
					//bootloader_status->error_count.error_count_ack_checksum++; // TODO
					loge("Error 2\n\r");
					spitfp_master_handle_protocol_error();
					return;
				}

				uint8_t last_sequence_number_seen_by_slave = (data_sequence_number & 0xF0) >> 4;
//				uartbb_printf("seq ack slave %d, cur %d\n\r", last_sequence_number_seen_by_slave, spitfp_master.current_sequence_number);
				if(last_sequence_number_seen_by_slave == spitfp_master.current_sequence_number) {
					spitfp_master.buffer_send_index = 0;
					spitfp_master.buffer_send_length = 0;
				}

				break;
			}

			case SPITFP_STATE_MESSAGE_SEQUENCE_NUMBER: {
				data_sequence_number = data;
				PEARSON(checksum, data_sequence_number);
				state = SPITFP_STATE_MESSAGE_DATA;
				break;
			}

			case SPITFP_STATE_MESSAGE_DATA: {
				message[message_position] = data;
				message_position++;

				PEARSON(checksum, data);

				if(message_position == data_length - SPITFP_PROTOCOL_OVERHEAD) {
					state = SPITFP_STATE_MESSAGE_CHECKSUM;
				}
				break;
			}

			case SPITFP_STATE_MESSAGE_CHECKSUM: {
				// Whatever happens here, we will go to start again
				state = SPITFP_STATE_START;

				// Remove data from ringbuffer. If we can't send it we can't handle
				// it at the moment we will wait for the SPI master to re-send it.
				ringbuffer_remove(&spitfp_master.ringbuffer_recv, num_to_remove_from_ringbuffer);
				num_to_remove_from_ringbuffer = 0;

				if(checksum != data) {
					//bootloader_status->error_count.error_count_message_checksum++; // TODO
					loge("Error 3\n\r");
					spitfp_master_handle_protocol_error();
					return;
				}

				uint8_t last_sequence_number_seen_by_slave = (data_sequence_number & 0xF0) >> 4;
//				uartbb_printf("seq msg slave %d, cur %d -> tmp len %d\n\r", last_sequence_number_seen_by_slave, spitfp_master.current_sequence_number, spitfp_master.buffer_recv_tmp_length);
				if(last_sequence_number_seen_by_slave == spitfp_master.current_sequence_number) {
					spitfp_master.buffer_send_index = 0;
					spitfp_master.buffer_send_length = 0;
				}

				// If we already have one recv message in the temporary buffer,
				// we don't handle the newly received message and just throw it away.
				// The SPI master will send it again.
				if(spitfp_master.buffer_recv_tmp_length == 0) {
					// If sequence number is new, we can handle the message.
					// Otherwise we only ACK the already handled message again.
					const uint8_t message_sequence_number = data_sequence_number & 0x0F;
					if((message_sequence_number != spitfp_master.last_sequence_number_seen) || (message_sequence_number == 1)) {
						// For the special case that the sequence number is 1 (only used for the very first message)
						// we always send an answer, even if we havn't seen anything else in between.
						// Otherwise it is not possible to reset the Master Brick if no messages were exchanged before
						// the reset

						spitfp_master.last_sequence_number_seen = message_sequence_number;
						// The handle message function will send an ACK for the message
						// if it can handle the message at the current moment.
						// Otherwise it will save the message and length for it it be send
						// later on.
						if(spitfp_master_is_send_possible() && communication_handle_message_from_bricklet(message, message_position)) {
							spitfp_master_send_ack();
						} else {
							spitfp_master.buffer_recv_tmp_length = message_position;
							memcpy(spitfp_master.buffer_recv_tmp, message, message_position);
						}
					} else {
						if(spitfp_master_is_send_possible()) {
							spitfp_master_send_ack();
						} else {
							// If we want to send an ACK but currently can't, we set the
							// temporary recv buffer length to SPITFP_PROTOCOL_OVERHEAD.
							spitfp_master.buffer_recv_tmp_length = SPITFP_PROTOCOL_OVERHEAD;
						}
					}
				}
				return;
			}
		}
	}
}

void spitfp_master_tick(void) {
	if(spitfp_master_is_send_possible()) {
		// If there is a message to be send from Brick to Bricklet we can send it now.
		if(spitfp_master.buffer_message_from_brick_length > 0) {
//			uartbb_printf("spitfp_master_tick send\n\r");
			spitfp_master_send_ack_and_message(spitfp_master.buffer_message_from_brick, spitfp_master.buffer_message_from_brick_length);
			spitfp_master.buffer_message_from_brick_length = 0;
		// Otherwise we will just send zeros here
		} else {
			spitfp_master_trigger_send();
		}
	} else if((SPITFP_MASTER_USIC->PCR_SSCMode & USIC_CH_PCR_SSCMode_SELO_Msk) == 0) {
		if(system_timer_is_time_elapsed_ms(spitfp_master.last_send_started, 1)) {
			spitfp_master_trigger_send();
		}
	}

	spitfp_master_check();
}