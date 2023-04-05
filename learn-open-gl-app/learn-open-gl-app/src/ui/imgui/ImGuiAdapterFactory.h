#pragma once

#include "../UiAdapterFactory.h"

class ImGuiAdapterFactory : public UiAdapterFactory
{
public:
	UiActorAdapter* CreateActorAdapter(Actor* actor) const override;
	UiComponentAdapter* CreateComponentAdapter(ActorComponent* component) const override;
};
