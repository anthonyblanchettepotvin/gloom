#include "ImGuiActorAdapter.h"

#include <cassert>
#include <memory>

#include "../../../vendor/imgui/imgui.h"

#include "../../../engine/object/ObjectType.h"
#include "../../../game/actor/Actor.h"
#include "../../../game/component/ActorComponent.h"

#include "../ImGuiAdapterFactory.h"

ImGuiActorAdapter::ImGuiActorAdapter(ImGuiAdapterFactory& adapterFactory, Actor& actor)
	: m_AdapterFactory(adapterFactory), m_Actor(actor)
{
}

void ImGuiActorAdapter::Render()
{
	ImGui::Text(m_Actor.GetName().c_str());

	for (const auto& component : m_Actor.GetComponents())
	{
		assert(component != nullptr);

		std::unique_ptr<ImGuiAdapter> componentAdapter = m_AdapterFactory.CreateAdapter(component);
		if (!componentAdapter)
		{
			continue;
		}

		if (ImGui::CollapsingHeader(component->GetObjectType().GetDisplayName().c_str()))
		{
			componentAdapter->Render();
		}
	}
}
