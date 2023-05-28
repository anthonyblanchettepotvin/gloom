#pragma once

#include "../../game/actor/Actor.h"

#include "../UiActorAdapter.h"

class ImGuiActorAdapter : public UiActorAdapter
{
public:
	ImGuiActorAdapter(Actor* actor);

	void RenderUi() const;
};
