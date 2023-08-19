#include "ImGuiDirectionalLightComponentAdapter.h"

#include <glm/gtc/type_ptr.hpp>

#include "../../vendor/imgui/imgui.h"

#include "../../game/component/DirectionalLightComponent.h"

ImGuiDirectionalLightComponentAdapter::ImGuiDirectionalLightComponentAdapter(DirectionalLightComponent* directionalLightComponent)
	: m_DirectionalLightComponent(directionalLightComponent)
{
}

void ImGuiDirectionalLightComponentAdapter::Render() const
{
	if (m_DirectionalLightComponent)
	{
		ImGui::InputFloat3("Direction", glm::value_ptr(m_DirectionalLightComponent->GetDirectionalLight()->GetDirectionReference()));
		ImGui::SliderFloat3("Ambient Color", glm::value_ptr(m_DirectionalLightComponent->GetDirectionalLight()->GetAmbientColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat3("Diffuse Color", glm::value_ptr(m_DirectionalLightComponent->GetDirectionalLight()->GetDiffuseColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat3("Specular Color", glm::value_ptr(m_DirectionalLightComponent->GetDirectionalLight()->GetSpecularColorReference()), 0.0f, 1.0f);
	}
}
