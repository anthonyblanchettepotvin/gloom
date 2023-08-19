#include "ImGuiActorAdapter.h"

#include "../../vendor/imgui/imgui.h"

#include "../../game/actor/Actor.h"

ImGuiActorAdapter::ImGuiActorAdapter(Actor* actor)
	: m_Actor(actor)
{
}

void ImGuiActorAdapter::Render() const
{
	if (m_Actor)
	{
		ImGui::Text(m_Actor->GetName().c_str());
	}
}
