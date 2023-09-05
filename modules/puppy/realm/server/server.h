#ifndef PUPPY_SERVER_H
#define PUPPY_SERVER_H

#include "modules/puppy/realms/puppy_realm.h"

class PuppyServer final : public PuppyRealm {
protected:
	Error _update() override;
	void _handle(const uint8_t *buffer, int len, int sender, int channel, MultiplayerPeer::TransferMode mode) override;

private:
	GDCLASS(PuppyServer, PuppyRealm)

public:
	using PuppyRealm::PuppyRealm; // Inherit constructor
};

#endif // PUPPY_SERVER_H
