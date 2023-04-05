#include "ImGuiActorAdapter.h"

#include "../../imgui/imgui.h"

ImGuiActorAdapter::ImGuiActorAdapter(Actor* actor)
	: UiActorAdapter(actor)
{
}

void ImGuiActorAdapter::RenderUi() const
{
	if (actor)
	{
		ImGui::Text(actor->GetName().c_str());
	}
}
