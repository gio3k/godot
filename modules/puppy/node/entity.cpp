#include "entity.h"

void Entity::simulate() {
	GDVIRTUAL_CALL(_simulate);
}

void Entity::_bind_methods() {
	BIND_CONSTANT(NOTIFICATION_SIMULATE);

	GDVIRTUAL_BIND(_simulate);
}

void Entity::_notification(int p_what) {
	if (p_what == NOTIFICATION_SIMULATE) {
		simulate();
	}
}
