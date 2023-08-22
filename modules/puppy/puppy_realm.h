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
