#include "ImGuiDirectionalLightComponentAdapter.h"

#include "../../imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

ImGuiDirectionalLightComponentAdapter::ImGuiDirectionalLightComponentAdapter(DirectionalLightComponent* component)
	: UiComponentAdapter(component)
{
}

void ImGuiDirectionalLightComponentAdapter::RenderUi() const
{
	if (DirectionalLightComponent* castedComponent = dynamic_cast<DirectionalLightComponent*>(component))
	{
		ImGui::InputFloat3("Direction", glm::value_ptr(castedComponent->GetDirectionReference()));
		ImGui::SliderFloat3("Ambient Color", glm::value_ptr(castedComponent->GetAmbientColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat3("Diffuse Color", glm::value_ptr(castedComponent->GetDiffuseColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat3("Specular Color", glm::value_ptr(castedComponent->GetSpecularColorReference()), 0.0f, 1.0f);
	}
}
