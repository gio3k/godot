/**************************************************************************/
/*  puppy_realm.h														  */
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

#ifndef PUPPY_REALM_H
#define PUPPY_REALM_H

#include "core/object/ref_counted.h"
#include "scene/main/multiplayer_peer.h"

class PuppyMultiplayer;
class PuppyRealm : public RefCounted {
	GDCLASS(PuppyRealm, RefCounted)

	friend PuppyMultiplayer;

	/**
	 * \brief Poll the peer and call update() if possible
	 */
	Error _poll();

	MultiplayerPeer::ConnectionStatus _connection_status = MultiplayerPeer::CONNECTION_DISCONNECTED;

protected:
	/**
	 * \brief This is our "peer" - we use this to talk to other peers.
	 * Keep in mind - this can be for a server, a client, or anything really. It's just used
	 * to communicate to other peers.
	 */
	Ref<MultiplayerPeer> _peer;

	/**
	 * \brief Puppy multiplayer core controller
	 */
	PuppyMultiplayer *_multiplayer;

	/**
	 * \brief Called every time the peer is polled
	 * \return Error
	 */
	virtual Error _update() = 0;

	/**
	 * \brief Called for every packet found after polling
	 * \param buffer Pointer to packet data
	 * \param len Packet length
	 * \param sender Packet sender
	 * \param channel Packet channel
	 * \param mode Packet transfer mode
	 */
	virtual void _handle(const uint8_t *buffer, int len, int sender, int channel, MultiplayerPeer::TransferMode mode) = 0;

public:
	explicit PuppyRealm(PuppyMultiplayer *p_multiplayer) {
		_multiplayer = p_multiplayer;
	}

	void set_multiplayer_peer(const Ref<MultiplayerPeer> &p_peer) {
		_peer = p_peer;
	}

	Ref<MultiplayerPeer> get_multiplayer_peer() {
		return _peer;
	}
};

#endif
