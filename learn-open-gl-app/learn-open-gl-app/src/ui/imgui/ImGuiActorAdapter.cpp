#include "ImGuiActorAdapter.h"

#include "../../vendor/imgui/imgui.h"

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
