﻿/**************************************************************************/
/*  puppy_realm.cpp                                                       */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "puppy_realm.h"

Error PuppyRealm::_poll() {
	Error err;

	if (!_peer.is_valid()) {
		// Invalid peer - set connection status to disconnected and return
		_connection_status = MultiplayerPeer::CONNECTION_DISCONNECTED;
		return OK;
	}

	// Update connection status
	_connection_status = _peer->get_connection_status();
	if (_connection_status != MultiplayerPeer::CONNECTION_CONNECTED)
		return OK; // We aren't connected - just return OK for now

	// Update the realm
	if (err = _update(); err != OK)
		return err;

	// Get all packets from peer, call _handle for each
	while (_peer->get_available_packet_count() != 0) {
		const int sender = _peer->get_packet_peer();
		const int channel = _peer->get_packet_channel();
		const MultiplayerPeer::TransferMode mode = _peer->get_packet_mode();

		const uint8_t *buffer;
		int len;

		// Attempt to get the packet
		err = _peer->get_packet(&buffer, len);
		ERR_FAIL_COND_V_MSG(err != OK, err, "Couldn't get packet while polling realm");

		// Call _handle
		_handle(buffer, len, sender, channel, mode);
	}

	// We're done here!
	return OK;
}

void PuppyRealm::_set_target_peer(const int p_peer_id) const {
	_peer->set_target_peer(p_peer_id);
}

void PuppyRealm::_send_to_peer(const uint8_t *p_buffer, const int p_len) const {
	_peer->put_packet(p_buffer, p_len);
}

void PuppyRealm::_set_transfer_mode(const MultiplayerPeer::TransferMode p_mode) const {
	_peer->set_transfer_mode(p_mode);
}

void PuppyRealm::_set_transfer_channel(const int p_channel) const {
	_peer->set_transfer_channel(p_channel);
}
