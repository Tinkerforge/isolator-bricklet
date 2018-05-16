/* isolator-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_spitfp.h: Configuration for SPI TF Protocol Master
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

#ifndef CONFIG_SPITFP_MASTER
#define CONFIG_SPITFP_MASTER

#include "xmc_gpio.h"
#include "xmc_spi.h"

#define SPITFP_MASTER_USIC_CHANNEL         USIC0_CH1
#define SPITFP_MASTER_USIC                 XMC_SPI0_CH1

#define SPITFP_MASTER_SCLK_PIN             P0_8
#define SPITFP_MASTER_SCLK_PIN_AF          (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7 | P0_8_AF_U0C1_SCLKOUT)

#define SPITFP_MASTER_SELECT_PIN           P0_9
#define SPITFP_MASTER_SELECT_PIN_AF        (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7 | P0_9_AF_U0C1_SELO0)

#define SPITFP_MASTER_MOSI_PIN             P0_7
#define SPITFP_MASTER_MOSI_PIN_AF          (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7 | P0_7_AF_U0C1_DOUT0)

#define SPITFP_MASTER_MISO_PIN             P0_6
#define SPITFP_MASTER_MISO_INPUT           XMC_USIC_CH_INPUT_DX0
#define SPITFP_MASTER_MISO_SOURCE          0b010 // DX0C

#define SPITFP_MASTER_SERVICE_REQUEST_RX   2
#define SPITFP_MASTER_SERVICE_REQUEST_TX   3

#define SPITFP_MASTER_IRQ_RX               11
#define SPITFP_MASTER_IRQ_RX_PRIORITY      1
#define SPITFP_MASTER_IRQ_TX               12
#define SPITFP_MASTER_IRQ_TX_PRIORITY      0

#define SPITFP_MASTER_TX_DATA_POINTER      48
#define SPITFP_MASTER_TX_SIZE              XMC_USIC_CH_FIFO_SIZE_16WORDS
#define SPITFP_MASTER_TX_LIMIT             8

#define SPITFP_MASTER_RX_DATA_POINTER      32
#define SPITFP_MASTER_RX_SIZE              XMC_USIC_CH_FIFO_SIZE_16WORDS
#define SPITFP_MASTER_RX_LIMIT             0

#endif