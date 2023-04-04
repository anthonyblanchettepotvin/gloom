#pragma once

#include "UiAdapter.h"

#include "../Actor.h"

class UiActorAdapter : public UiAdapter
{
public:
	UiActorAdapter(Actor* actor);

protected:
	Actor* actor;
};
