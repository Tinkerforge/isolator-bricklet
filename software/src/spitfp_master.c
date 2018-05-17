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
#include "bricklib2/utility/util_definitions.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/protocols/spitfp/spitfp.h"

#define spitfp_master_rx_irq_handler IRQ_Hdlr_11
#define spitfp_master_tx_irq_handler IRQ_Hdlr_12

SPITFPMaster spitfp_master;

// This interrupt is automtically called if the TX buffer goes from 9 bytes to 8 bytes.
// It is also called directly from the code everytime when data has to be send.
void __attribute__((optimize("-O3"))) __attribute__((section (".ram_code"))) spitfp_master_tx_irq_handler(void) {
	while(!XMC_USIC_CH_TXFIFO_IsFull(SPITFP_MASTER_USIC)) {
		if(spitfp_master.buffer_send_index < spitfp_master.buffer_send_length) {
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
			// If we don't have any data to send, will will send zeroes to poll the slave.
			// The amount of zeroes to be send is set by the state machine.
			if(spitfp_master.bytes_to_read > 0) {
				spitfp_master.bytes_to_read--;
				SPITFP_MASTER_USIC->IN[0] = 0;
			} else {
				return;
			}
		}
	}
}

void __attribute__((optimize("-O3"))) __attribute__((section (".ram_code"))) spitfp_master_rx_irq_handler(void) {
	// If this interrupt is called we always have at least 8 bytes available.
	spitfp_master.buffer_recv[spitfp_master.ringbuffer_recv.end] = SPITFP_MASTER_USIC->OUTR;
	spitfp_master.ringbuffer_recv.end = (spitfp_master.ringbuffer_recv.end + 1) & SPITFP_MASTER_BUFFER_MASK;
	spitfp_master.buffer_recv[spitfp_master.ringbuffer_recv.end] = SPITFP_MASTER_USIC->OUTR;
	spitfp_master.ringbuffer_recv.end = (spitfp_master.ringbuffer_recv.end + 1) & SPITFP_MASTER_BUFFER_MASK;
	spitfp_master.buffer_recv[spitfp_master.ringbuffer_recv.end] = SPITFP_MASTER_USIC->OUTR;
	spitfp_master.ringbuffer_recv.end = (spitfp_master.ringbuffer_recv.end + 1) & SPITFP_MASTER_BUFFER_MASK;
	spitfp_master.buffer_recv[spitfp_master.ringbuffer_recv.end] = SPITFP_MASTER_USIC->OUTR;
	spitfp_master.ringbuffer_recv.end = (spitfp_master.ringbuffer_recv.end + 1) & SPITFP_MASTER_BUFFER_MASK;
	spitfp_master.buffer_recv[spitfp_master.ringbuffer_recv.end] = SPITFP_MASTER_USIC->OUTR;
	spitfp_master.ringbuffer_recv.end = (spitfp_master.ringbuffer_recv.end + 1) & SPITFP_MASTER_BUFFER_MASK;
	spitfp_master.buffer_recv[spitfp_master.ringbuffer_recv.end] = SPITFP_MASTER_USIC->OUTR;
	spitfp_master.ringbuffer_recv.end = (spitfp_master.ringbuffer_recv.end + 1) & SPITFP_MASTER_BUFFER_MASK;
	spitfp_master.buffer_recv[spitfp_master.ringbuffer_recv.end] = SPITFP_MASTER_USIC->OUTR;
	spitfp_master.ringbuffer_recv.end = (spitfp_master.ringbuffer_recv.end + 1) & SPITFP_MASTER_BUFFER_MASK;
	spitfp_master.buffer_recv[spitfp_master.ringbuffer_recv.end] = SPITFP_MASTER_USIC->OUTR;
	spitfp_master.ringbuffer_recv.end = (spitfp_master.ringbuffer_recv.end + 1) & SPITFP_MASTER_BUFFER_MASK;
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

	// Disable Frame End Mode. This means that a slave select gets automatically deasserted if the last
	// bit has been shifted out of the out register.

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
	XMC_USIC_CH_TXFIFO_EnableEvent(SPITFP_MASTER_USIC, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);

	XMC_SPI_CH_DisableFEM(SPITFP_MASTER_USIC);
	XMC_SPI_CH_EnableSlaveSelect(SPITFP_MASTER_USIC, XMC_SPI_CH_SLAVE_SELECT_0);
}

void spitfp_master_init(void) {
	memset(&spitfp_master, 0, sizeof(SPITFPMaster));
	ringbuffer_init(&spitfp_master.ringbuffer_recv, SPITFP_MASTER_BUFFER_LENGTH, spitfp_master.buffer_recv);

    spitfp_master_init_spi();
}

void spitfp_master_trigger_send(void) {
	// We turn tx IRQ off while we call the handler by hand, to be 100% sure that we can't
	// get the interrupt while in the interrupt
	XMC_USIC_CH_TXFIFO_DisableEvent(SPITFP_MASTER_USIC, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);
	spitfp_master_tx_irq_handler();
	XMC_USIC_CH_TXFIFO_EnableEvent(SPITFP_MASTER_USIC, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);
}

uint8_t spitfp_master_get_sequence_byte(const bool increase) {
	if(increase) {
		spitfp_master.current_sequence_number++;
		if(spitfp_master.current_sequence_number > 0xF) {
			spitfp_master.current_sequence_number = 2;
		}
	}

	return spitfp_master.current_sequence_number | (spitfp_master.last_sequence_number_seen << 4);
}

void spitfp_master_send_ack_and_message(uint8_t *data, const uint8_t length) {
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

	spitfp_master.last_send_started = system_timer_get_ms();
	spitfp_master_trigger_send();
}

void spitfp_master_send_ack(void) {
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

	spitfp_master.last_send_started = system_timer_get_ms();
	spitfp_master_trigger_send();
}

bool spitfp_master_is_send_possible(void) {
	 return spitfp_master.buffer_send_length == 0;
}

void spitfp_master_check_message_send_timeout(void) {
	// If we are not currently sending a message
	// and there is still data in the buffer 
	// and the timeout ran out we resend the message
	if((spitfp_master.buffer_send_length > SPITFP_PROTOCOL_OVERHEAD) && 
	   (spitfp_master.buffer_send_length == spitfp_master.buffer_send_index) && 
	   (system_timer_is_time_elapsed_ms(spitfp_master.last_send_started, SPITFP_TIMEOUT) || spitfp_master.ack_to_send)) {

		// Update sequence number of send buffer. We don't increase the current sequence
		// number, but if we have seen a new message from the master we insert
		// the updated "last seen sequence number".
		// If the number changed we also have to update the checksum.
		uint8_t new_sequence_byte = spitfp_master_get_sequence_byte(false);
		if(new_sequence_byte != spitfp_master.buffer_send[1]) {
			spitfp_master.buffer_send[1] = new_sequence_byte;
			uint8_t checksum = 0;
			for(uint8_t i = 0; i < spitfp_master.buffer_send[0]-1; i++) {
				PEARSON(checksum, spitfp_master.buffer_send[i]);
			}

			spitfp_master.buffer_send[spitfp_master.buffer_send[0]-1] = checksum;
		}
	
		spitfp_master.buffer_send_index = 0;
		spitfp_master.ack_to_send = false;
		spitfp_master.last_send_started = system_timer_get_ms();
		spitfp_master_trigger_send();
	}
}

void spitfp_master_handle_protocol_error(void) {
	// In case of error we completely empty the ringbuffer
	uint8_t data;
	while(ringbuffer_get(&spitfp_master.ringbuffer_recv, &data));
}

void spitfp_master_check_message(void) {
	// If the temporary buffer length is > 0 we still have a message to handle
	if(spitfp_master.buffer_recv_tmp_length > 0) {
		// Try to send message to Bricklet
		if(communication_handle_message_from_bricklet(spitfp_master.buffer_recv_tmp, spitfp_master.buffer_recv_tmp_length)) {
			spitfp_master.buffer_recv_tmp_length = 0;

			// If we were able to send message to Bricklet, try to send ACK
			if(spitfp_master_is_send_possible()) {
				spitfp_master_send_ack();
			} else {
				// If we can't send the ack we set a flag here and the ACK is send later on.
				// If we aren't fast enough the slave may send us a duplicate of the message,
				// but the duplicate will be thrown away since the sequence number will not
				// be incresead in the meantime.
				spitfp_master.ack_to_send = true;
			}
		}
	}

	// Check if we didn't receive an ACK within the timeout time and resend the message if necessary.
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
					spitfp_master_handle_protocol_error();
					return;
				}

				uint8_t last_sequence_number_seen_by_slave = (data_sequence_number & 0xF0) >> 4;
				if(last_sequence_number_seen_by_slave == spitfp_master.current_sequence_number) {
					// If we got a timeout and are now re-sending the message, it
					// is possible that we are currently sending this message again.
					// Check if it was send completely
					if(spitfp_master.buffer_send_index == spitfp_master.buffer_send_length) {
						spitfp_master.buffer_send_index = 0;
						spitfp_master.buffer_send_length = 0;
					}
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
					spitfp_master_handle_protocol_error();
					return;
				}

				uint8_t last_sequence_number_seen_by_slave = (data_sequence_number & 0xF0) >> 4;
				if(last_sequence_number_seen_by_slave == spitfp_master.current_sequence_number) {
					// If we got a timeout and are now re-sending the message, it
					// is possible that we are currently sending this message again.
					// Check if it was send completely
					if(spitfp_master.buffer_send_index == spitfp_master.buffer_send_length) {
						spitfp_master.buffer_send_index = 0;
						spitfp_master.buffer_send_length = 0;
					}
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
						if(communication_handle_message_from_bricklet(message, message_position)) {
							if(spitfp_master_is_send_possible()) {
								spitfp_master_send_ack();
							} else {
								spitfp_master.ack_to_send = true;
							}
						} else {
							spitfp_master.buffer_recv_tmp_length = message_position;
							memcpy(spitfp_master.buffer_recv_tmp, message, message_position);
						}
					} else {
						if(spitfp_master_is_send_possible()) {
							spitfp_master_send_ack();
						} else {
							spitfp_master.ack_to_send = true;
						}
					}
				}
				return;
			}
		}
	}
}

uint16_t spitfp_master_check_missing_length() {
	// Peak into the buffer to get the message length.
	// Only call this before or after bricklet_co_mcu_check_recv.
	Ringbuffer *rb = &spitfp_master.ringbuffer_recv;
	while(rb->start != rb->end) {
		uint8_t length = rb->buffer[rb->start];
		if((length < SPITFP_MIN_TFP_MESSAGE_LENGTH || length > SPITFP_MAX_TFP_MESSAGE_LENGTH) && length != SPITFP_PROTOCOL_OVERHEAD) {
			ringbuffer_remove(rb, 1);
			continue;
		}

		int32_t ret = length - ringbuffer_get_used(rb);
		if((ret < 0) || (ret > TFP_MESSAGE_MAX_LENGTH)) {
			return 0;
		}

		return ret;
	}

	return 0;
}

void spitfp_master_poll_spi_recv_fifo(void) {
	// Turn the RX fifo interrupt off, to be sure that we can't get an interrupt while we are polling here
	XMC_USIC_CH_RXFIFO_DisableEvent(SPITFP_MASTER_USIC, XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD | XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE);
	while(!XMC_USIC_CH_RXFIFO_IsEmpty(SPITFP_MASTER_USIC)) {
		spitfp_master.buffer_recv[spitfp_master.ringbuffer_recv.end] = SPITFP_MASTER_USIC->OUTR;
		spitfp_master.ringbuffer_recv.end = (spitfp_master.ringbuffer_recv.end + 1) & SPITFP_MASTER_BUFFER_MASK;
	}
	XMC_USIC_CH_RXFIFO_EnableEvent(SPITFP_MASTER_USIC, XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD | XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE);
}

void spitfp_master_tick(void) {
	spitfp_master_trigger_send();

	spitfp_master_poll_spi_recv_fifo();
	spitfp_master_check_message();

	spitfp_master_poll_spi_recv_fifo();
	const uint16_t missing_length = spitfp_master_check_missing_length();
	spitfp_master.bytes_to_read = MAX(missing_length, spitfp_master.bytes_to_read);

	if(spitfp_master_is_send_possible()) {
		// If there is a message to be send from Brick to Bricklet we can send it now.
		if(spitfp_master.buffer_message_from_brick_length > 0) {
			spitfp_master_send_ack_and_message(spitfp_master.buffer_message_from_brick, spitfp_master.buffer_message_from_brick_length);
			spitfp_master.buffer_message_from_brick_length = 0;
			return;
		// If there is an ack to be send, we can send it now.
		} else if(spitfp_master.ack_to_send) {
			spitfp_master_send_ack();
			spitfp_master.ack_to_send = false;
			return;
		}
	}

	// If we can't send data or ack (see above) and the last time we polled the slave
	// was over 1ms ago, we poll again.
	if(system_timer_is_time_elapsed_ms(spitfp_master.last_poll, 1) || (spitfp_master.bytes_to_read > 0)) {
		spitfp_master.last_poll = system_timer_get_ms();
		spitfp_master.bytes_to_read = MAX(1, spitfp_master.bytes_to_read);
		spitfp_master_trigger_send();
	}
}