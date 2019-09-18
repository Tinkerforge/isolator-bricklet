/* isolator-bricklet
 * Copyright (C) 2018-2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.h: TFP protocol message handling
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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/bootloader/bootloader.h"

// Default functions
BootloaderHandleMessageResponse handle_message(const void *data, void *response);
void communication_tick(void);
void communication_init(void);

// Constants

#define ISOLATOR_BOOTLOADER_MODE_BOOTLOADER 0
#define ISOLATOR_BOOTLOADER_MODE_FIRMWARE 1
#define ISOLATOR_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2
#define ISOLATOR_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3
#define ISOLATOR_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

#define ISOLATOR_BOOTLOADER_STATUS_OK 0
#define ISOLATOR_BOOTLOADER_STATUS_INVALID_MODE 1
#define ISOLATOR_BOOTLOADER_STATUS_NO_CHANGE 2
#define ISOLATOR_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3
#define ISOLATOR_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4
#define ISOLATOR_BOOTLOADER_STATUS_CRC_MISMATCH 5

#define ISOLATOR_STATUS_LED_CONFIG_OFF 0
#define ISOLATOR_STATUS_LED_CONFIG_ON 1
#define ISOLATOR_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2
#define ISOLATOR_STATUS_LED_CONFIG_SHOW_STATUS 3

// Function and callback IDs and structs
#define FID_GET_STATISTICS 1
#define FID_SET_SPITFP_BAUDRATE_CONFIG 2
#define FID_GET_SPITFP_BAUDRATE_CONFIG 3
#define FID_SET_SPITFP_BAUDRATE 4
#define FID_GET_SPITFP_BAUDRATE 5
#define FID_GET_ISOLATOR_SPITFP_ERROR_COUNT 6
#define FID_SET_STATISTICS_CALLBACK_CONFIGURATION 7
#define FID_GET_STATISTICS_CALLBACK_CONFIGURATION 8

#define FID_CALLBACK_STATISTICS 9

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetStatistics;

typedef struct {
	TFPMessageHeader header;
	uint32_t messages_from_brick;
	uint32_t messages_from_bricklet;
	uint16_t connected_bricklet_device_identifier;
	char connected_bricklet_uid[8];
} __attribute__((__packed__)) GetStatistics_Response;

typedef struct {
	TFPMessageHeader header;
	bool enable_dynamic_baudrate;
	uint32_t minimum_dynamic_baudrate;
} __attribute__((__packed__)) SetSPITFPBaudrateConfig;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetSPITFPBaudrateConfig;

typedef struct {
	TFPMessageHeader header;
	bool enable_dynamic_baudrate;
	uint32_t minimum_dynamic_baudrate;
} __attribute__((__packed__)) GetSPITFPBaudrateConfig_Response;

typedef struct {
	TFPMessageHeader header;
	uint32_t baudrate;
} __attribute__((__packed__)) SetSPITFPBaudrate;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetSPITFPBaudrate;

typedef struct {
	TFPMessageHeader header;
	uint32_t baudrate;
} __attribute__((__packed__)) GetSPITFPBaudrate_Response;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetIsolatorSPITFPErrorCount;

typedef struct {
	TFPMessageHeader header;
	uint32_t error_count_ack_checksum;
	uint32_t error_count_message_checksum;
	uint32_t error_count_frame;
	uint32_t error_count_overflow;
} __attribute__((__packed__)) GetIsolatorSPITFPErrorCount_Response;

typedef struct {
	TFPMessageHeader header;
	uint32_t period;
	bool value_has_to_change;
} __attribute__((__packed__)) SetStatisticsCallbackConfiguration;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetStatisticsCallbackConfiguration;

typedef struct {
	TFPMessageHeader header;
	uint32_t period;
	bool value_has_to_change;
} __attribute__((__packed__)) GetStatisticsCallbackConfiguration_Response;

typedef struct {
	TFPMessageHeader header;
	uint32_t messages_from_brick;
	uint32_t messages_from_bricklet;
	uint16_t connected_bricklet_device_identifier;
	char connected_bricklet_uid[8];
} __attribute__((__packed__)) Statistics_Callback;


// Function prototypes
BootloaderHandleMessageResponse get_statistics(const GetStatistics *data, GetStatistics_Response *response);
BootloaderHandleMessageResponse set_spitfp_baudrate_config(const SetSPITFPBaudrateConfig *data);
BootloaderHandleMessageResponse get_spitfp_baudrate_config(const GetSPITFPBaudrateConfig *data, GetSPITFPBaudrateConfig_Response *response);
BootloaderHandleMessageResponse set_spitfp_baudrate(const SetSPITFPBaudrate *data);
BootloaderHandleMessageResponse get_spitfp_baudrate(const GetSPITFPBaudrate *data, GetSPITFPBaudrate_Response *response);
BootloaderHandleMessageResponse get_isolator_spitfp_error_count(const GetIsolatorSPITFPErrorCount *data, GetIsolatorSPITFPErrorCount_Response *response);
BootloaderHandleMessageResponse set_statistics_callback_configuration(const SetStatisticsCallbackConfiguration *data);
BootloaderHandleMessageResponse get_statistics_callback_configuration(const GetStatisticsCallbackConfiguration *data, GetStatisticsCallbackConfiguration_Response *response);

// Callbacks
bool handle_statistics_callback(void);

#define COMMUNICATION_CALLBACK_TICK_WAIT_MS 1
#define COMMUNICATION_CALLBACK_HANDLER_NUM 1
#define COMMUNICATION_CALLBACK_LIST_INIT \
	handle_statistics_callback, \


#endif
