#include "ImGuiPointLightComponentAdapter.h"

#include <glm/gtc/type_ptr.hpp>

#include "../../../vendor/imgui/imgui.h"

#include "../../../game/component/PointLightComponent.h"

ImGuiPointLightComponentAdapter::ImGuiPointLightComponentAdapter(PointLightComponent& pointLightComponent)
	: m_PointLightComponent(pointLightComponent)
{
}

void ImGuiPointLightComponentAdapter::Render() const
{
	if (m_PointLightComponent.GetPointLight())
	{
		ImGui::ColorEdit3("Ambient Color", glm::value_ptr(m_PointLightComponent.GetPointLight()->GetAmbientColor()));
		ImGui::ColorEdit3("Diffuse Color", glm::value_ptr(m_PointLightComponent.GetPointLight()->GetDiffuseColor()));
		ImGui::ColorEdit3("Specular Color", glm::value_ptr(m_PointLightComponent.GetPointLight()->GetSpecularColor()));
		ImGui::SliderFloat("Constant", &m_PointLightComponent.GetPointLight()->GetAttenuation().Constant, 0.0f, 2.0f);
		ImGui::SliderFloat("Linear", &m_PointLightComponent.GetPointLight()->GetAttenuation().Linear, 0.0f, 2.0f);
		ImGui::SliderFloat("Quadratic", &m_PointLightComponent.GetPointLight()->GetAttenuation().Quadratic, 0.0f, 2.0f);
	}
}
