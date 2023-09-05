#ifndef PUPPY_ENTITY_H
#define PUPPY_ENTITY_H

#include "scene/main/node.h"

class Entity : public Node {
	GDCLASS(Entity, Node)

public:
	enum {
		NOTIFICATION_SIMULATE = 44
	};

	GDVIRTUAL0(_simulate);
	virtual void simulate();

protected:
	static void _bind_methods();
	void _notification(int p_what);
};

#endif // PUPPY_ENTITY_H
