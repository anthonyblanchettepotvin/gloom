#include "ImGuiActorAdapter.h"

#include "../../../vendor/imgui/imgui.h"

#include "../../../game/actor/Actor.h"
#include "../../../game/component/ActorComponent.h"

#include "../ImGuiAdapterFactory.h"

ImGuiActorAdapter::ImGuiActorAdapter(const ImGuiAdapterFactory& adapterFactory, Actor& actor)
	: m_AdapterFactory(adapterFactory), m_Actor(actor)
{
}

void ImGuiActorAdapter::Render() const
{
	ImGui::Text(m_Actor.GetName().c_str());

	for (const auto& component : m_Actor.GetComponents())
	{
		ImGui::Separator();

		ImGuiAdapter* componentAdapter = m_AdapterFactory.CreateAdapter(component);
		if (componentAdapter)
		{
			componentAdapter->Render();
		}
	}
}
