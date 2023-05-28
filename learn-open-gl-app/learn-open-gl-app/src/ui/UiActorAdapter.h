#pragma once

#include "UiAdapter.h"

#include "../game/actor/Actor.h"

class UiActorAdapter : public UiAdapter
{
public:
	UiActorAdapter(Actor* actor);

protected:
	Actor* actor;
};
