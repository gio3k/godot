#pragma once
#include "realms/client/puppy_client.h"
#include "realms/server/puppy_server.h"
#include "scene/main/multiplayer_api.h"

class PuppyMultiplayer : public MultiplayerAPI {
	GDCLASS(PuppyMultiplayer, MultiplayerAPI)

	/**
	 * \brief The server controller for this multiplayer instance
	 */
	Ref<PuppyServer> server;

	/**
	 * \brief The client controller for this multiplayer instance
	 */
	Ref<PuppyClient> client;

protected:
	static void _bind_methods();

public:
	virtual void set_multiplayer_peer(const Ref<MultiplayerPeer> &p_peer) override;
	virtual Ref<MultiplayerPeer> get_multiplayer_peer() override;

	virtual Error poll() override;
	virtual int get_unique_id() override;
	virtual Vector<int> get_peer_ids() override;
	virtual int get_remote_sender_id() override;

	virtual Error rpcp(Object *p_obj, int p_peer_id, const StringName &p_method, const Variant **p_arg, int p_argcount) override;

	virtual Error object_configuration_add(Object *p_obj, Variant p_config) override;
	virtual Error object_configuration_remove(Object *p_obj, Variant p_config) override;

	PuppyMultiplayer();
};
