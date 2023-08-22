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
