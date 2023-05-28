#pragma once

#include "UiActorAdapter.h"
#include "UiComponentAdapter.h"

#include "../game/actor/Actor.h"
#include "../game/component/ActorComponent.h"

class UiAdapterFactory
{
public:
	virtual UiActorAdapter* CreateActorAdapter(Actor* actor) const = 0;
	virtual UiComponentAdapter* CreateComponentAdapter(ActorComponent* component) const = 0;
};
