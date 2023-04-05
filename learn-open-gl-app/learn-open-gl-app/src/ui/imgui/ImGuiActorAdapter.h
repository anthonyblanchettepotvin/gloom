#pragma once

#include "../../Actor.h"

#include "../UiActorAdapter.h"

class ImGuiActorAdapter : public UiActorAdapter
{
public:
	ImGuiActorAdapter(Actor* actor);

	void RenderUi() const;
};
