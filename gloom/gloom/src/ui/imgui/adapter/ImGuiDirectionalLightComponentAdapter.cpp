#include "ImGuiDirectionalLightComponentAdapter.h"

#include <glm/gtc/type_ptr.hpp>

#include "../../../vendor/imgui/imgui.h"

#include "../../../game/component/DirectionalLightComponent.h"

ImGuiDirectionalLightComponentAdapter::ImGuiDirectionalLightComponentAdapter(DirectionalLightComponent& directionalLightComponent)
	: m_DirectionalLightComponent(directionalLightComponent)
{
}

void ImGuiDirectionalLightComponentAdapter::Render() const
{
	if (m_DirectionalLightComponent.GetDirectionalLight())
	{
		ImGui::InputFloat3("Direction", glm::value_ptr(m_DirectionalLightComponent.GetDirectionalLight()->GetDirectionReference()));
		ImGui::ColorEdit3("Ambient Color", glm::value_ptr(m_DirectionalLightComponent.GetDirectionalLight()->GetAmbientColorReference()));
		ImGui::ColorEdit3("Diffuse Color", glm::value_ptr(m_DirectionalLightComponent.GetDirectionalLight()->GetDiffuseColorReference()));
		ImGui::ColorEdit3("Specular Color", glm::value_ptr(m_DirectionalLightComponent.GetDirectionalLight()->GetSpecularColorReference()));
	}
}
