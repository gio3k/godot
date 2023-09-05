#include "puppy_multiplayer.h"

void PuppyMultiplayer::_bind_methods() {
}
void PuppyMultiplayer::set_multiplayer_peer(const Ref<MultiplayerPeer> &p_peer) {
}
Ref<MultiplayerPeer> PuppyMultiplayer::get_multiplayer_peer() {
	return Ref<MultiplayerPeer>();
}
/**
 * \brief This is called every process iteration of the SceneTree.
 * We'll do most of the multiplayer work here.
 * \return Error
 */
Error PuppyMultiplayer::poll() {
	Error err = server->_poll();
	ERR_FAIL_COND_V_MSG(err != OK, err, vformat("Failed to update the Puppy server - %d", err));

	err = client->_poll();
	ERR_FAIL_COND_V_MSG(err != OK, err, vformat("Failed to update the Puppy client - %d", err));

	return OK;
}
int PuppyMultiplayer::get_unique_id() {
	WARN_PRINT("get_unique_id");
	return 0;
}
Vector<int> PuppyMultiplayer::get_peer_ids() {
	WARN_PRINT("get_peer_ids");
	return Vector<int>();
}
int PuppyMultiplayer::get_remote_sender_id() {
	WARN_PRINT("get_remote_sender_id");
	return 0;
}
Error PuppyMultiplayer::rpcp(Object *p_obj, int p_peer_id, const StringName &p_method, const Variant **p_arg, int p_argcount) {
	WARN_PRINT("rpcp");
	return OK;
}
Error PuppyMultiplayer::object_configuration_add(Object *p_obj, Variant p_config) {
	WARN_PRINT("object_configuration_add");
	return OK;
}
Error PuppyMultiplayer::object_configuration_remove(Object *p_obj, Variant p_config) {
	WARN_PRINT("object_configuration_remove");
	return OK;
}

PuppyMultiplayer::PuppyMultiplayer() {
	server = Ref(memnew(PuppyServer(this)));
	//client = Ref(memnew(PuppyClient(this)));
}
