#pragma once

#include "../../engine/object/Object.h"

class Actor;

class ActorComponent : public Object
{
public:
	virtual ~ActorComponent() = default;

	void SetParent(Actor* parent) { this->parent = parent; };

protected:
	Actor* parent;
};
