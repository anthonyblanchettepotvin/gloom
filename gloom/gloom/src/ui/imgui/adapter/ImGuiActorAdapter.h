#pragma once

#include "../ImGuiAdapter.h"

class Actor;
class ImGuiAdapterFactory;

class ImGuiActorAdapter : public ImGuiAdapter
{
public:
	ImGuiActorAdapter(ImGuiAdapterFactory& adapterFactory, Actor& actor);

	void Render() override;

private:
	ImGuiAdapterFactory& m_AdapterFactory;

	Actor& m_Actor;
};
