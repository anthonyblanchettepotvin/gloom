#pragma once

#include "ImGuiAdapter.h"

class Actor;

class ImGuiActorAdapter : public ImGuiAdapter
{
public:
	ImGuiActorAdapter(Actor* actor);

	void Render() const override;

private:
	Actor* m_Actor;
};
