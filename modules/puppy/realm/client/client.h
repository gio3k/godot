#ifndef PUPPY_CLIENT_H
#define PUPPY_CLIENT_H

#include "modules/puppy/realm/realm.h"

class PuppyClient final : public PuppyRealm {
	GDCLASS(PuppyClient, PuppyRealm)

public:
	using PuppyRealm::PuppyRealm; // Inherit constructor
};

#endif // PUPPY_CLIENT_H
