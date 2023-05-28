#pragma once

#include "UiAdapter.h"

#include "../game/component/ActorComponent.h"

class UiComponentAdapter : public UiAdapter
{
public:
	UiComponentAdapter(ActorComponent* component);

protected:
	ActorComponent* component;
};
