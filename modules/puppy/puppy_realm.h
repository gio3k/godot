#ifndef PUPPY_REALM_H
#define PUPPY_REALM_H

#include "core/object/ref_counted.h"
#include "scene/main/multiplayer_peer.h"

class PuppyMultiplayer;
class PuppyRealm : public RefCounted {
	GDCLASS(PuppyRealm, RefCounted)

protected:
	/**
	 * \brief This is our "peer" - we use this to talk to other "peers" over the internet.
	 * Keep in mind this can be a server or client, or anything really. It's just a way to talk
	 * to other peers.
	 */
	Ref<MultiplayerPeer> peer;

public:
	explicit PuppyRealm(PuppyMultiplayer *core);

	void set_multiplayer_peer(const Ref<MultiplayerPeer> &p_peer) {
		peer = p_peer;
	}

	Ref<MultiplayerPeer> get_multiplayer_peer() {
		return peer;
	}
};

#endif
