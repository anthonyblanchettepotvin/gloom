#pragma once

class Actor;

class ActorComponent
{
public:
	virtual ~ActorComponent() = default;

	void SetParent(Actor* parent) { this->parent = parent; };

protected:
	Actor* parent;
};
