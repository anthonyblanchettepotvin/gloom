#pragma once

#include "UiActorAdapter.h"
#include "UiComponentAdapter.h"

#include "../Actor.h"
#include "../components/ActorComponent.h"

class UiAdapterFactory
{
public:
	virtual UiActorAdapter* CreateActorAdapter(Actor* actor) const = 0;
	virtual UiComponentAdapter* CreateComponentAdapter(ActorComponent* component) const = 0;
};
