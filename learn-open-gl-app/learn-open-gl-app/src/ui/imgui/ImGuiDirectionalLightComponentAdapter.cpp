#include "ImGuiDirectionalLightComponentAdapter.h"

#include "../../vendor/imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

ImGuiDirectionalLightComponentAdapter::ImGuiDirectionalLightComponentAdapter(DirectionalLightComponent* component)
	: UiComponentAdapter(component)
{
}

void ImGuiDirectionalLightComponentAdapter::RenderUi() const
{
	if (DirectionalLightComponent* castedComponent = dynamic_cast<DirectionalLightComponent*>(component))
	{
		ImGui::InputFloat3("Direction", glm::value_ptr(castedComponent->GetDirectionalLight()->GetDirectionReference()));
		ImGui::SliderFloat3("Ambient Color", glm::value_ptr(castedComponent->GetDirectionalLight()->GetAmbientColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat3("Diffuse Color", glm::value_ptr(castedComponent->GetDirectionalLight()->GetDiffuseColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat3("Specular Color", glm::value_ptr(castedComponent->GetDirectionalLight()->GetSpecularColorReference()), 0.0f, 1.0f);
	}
}
