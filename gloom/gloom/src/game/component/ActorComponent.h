#pragma once

#include "../../engine/object/Object.h"

class Actor;

class ActorComponent : public Object
{
public:
	virtual ~ActorComponent() = default;

	void SetParent(Actor* parent) { m_Parent = parent; }

protected:
	Actor* m_Parent = nullptr;
};
