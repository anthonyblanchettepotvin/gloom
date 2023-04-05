#pragma once

#include "UiAdapter.h"

#include "../components/ActorComponent.h"

class UiComponentAdapter : public UiAdapter
{
public:
	UiComponentAdapter(ActorComponent* component);

protected:
	ActorComponent* component;
};
