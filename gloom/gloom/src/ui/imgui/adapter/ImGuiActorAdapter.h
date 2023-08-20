#pragma once

#include "../ImGuiAdapter.h"

class Actor;
class ImGuiAdapterFactory;

class ImGuiActorAdapter : public ImGuiAdapter
{
public:
	ImGuiActorAdapter(const ImGuiAdapterFactory& adapterFactory, Actor& actor);

	void Render() const override;

private:
	const ImGuiAdapterFactory& m_AdapterFactory;

	Actor& m_Actor;
};
