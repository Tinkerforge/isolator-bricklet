/* isolator-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.c: TFP protocol message handling
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

#include "communication.h"

#include <string.h>

#include "bricklib2/utility/communication_callback.h"
#include "bricklib2/protocols/tfp/tfp.h"

#include "spitfp_master.h"

void communication_inspect_message_from_bricklet_to_brick(void *message) {
	const uint8_t fid = tfp_get_fid_from_message(message);

	char uid[9] = {'\0'};
	tfp_uid_uint32_to_base58(tfp_get_uid_from_message(message), uid);

	switch(fid) {
		case TFP_FID_ENUMERATE_CALLBACK:
		case TFP_FID_GET_IDENTITY: {
			TFPGetIdentityReturn *gir = message;

			// Insert correct position and connected UID into
			// enumerate and identity messages
			gir->position = 'I';
			memset(gir->connected_uid, '\0', TFP_UID_STR_MAX_LENGTH);
			tfp_uid_uint32_to_base58(bootloader_get_uid(), gir->connected_uid);
		}
	}
}

BootloaderHandleMessageResponse handle_message(const void *message, void *response) {
	const uint32_t message_uid = tfp_get_uid_from_message(message);
	// If message is for isolator we handle it here
	if(message_uid == bootloader_get_uid()) {
		switch(tfp_get_fid_from_message(message)) {

			default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
		}
	}
	
	// If there is space for a new message from the Brick we store it
	while(spitfp_master.buffer_message_from_brick_length != 0) {
		spitfp_master_tick();
	}

	const uint8_t length = tfp_get_length_from_message(message);
	memcpy(spitfp_master.buffer_message_from_brick, message, length);
	spitfp_master.buffer_message_from_brick_length = length;

#if 0
	// If there is data available to be send to bricklet we can send it here
	if(spitfp_master.buffer_message_from_bricklet_length > 0) {
		memcpy(response, spitfp_master.buffer_message_from_bricklet, spitfp_master.buffer_message_from_bricklet_length);
		spitfp_master.buffer_message_from_bricklet_length = 0;

		communication_inspect_message_from_bricklet_to_brick(response);

		return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
	}
#endif

	return HANDLE_MESSAGE_RESPONSE_NONE;
}

bool communication_handle_message_from_bricklet(uint8_t *message, const uint8_t length) {
	if(bootloader_spitfp_is_send_possible(&bootloader_status.st)) {
		communication_inspect_message_from_bricklet_to_brick(message);
		bootloader_spitfp_send_ack_and_message(&bootloader_status, message, length);
		return true;
	}

	return false;
}

void communication_tick(void) {
}

void communication_init(void) {
}
