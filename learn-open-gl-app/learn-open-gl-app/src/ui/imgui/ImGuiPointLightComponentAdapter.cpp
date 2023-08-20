#include "ImGuiPointLightComponentAdapter.h"

#include <glm/gtc/type_ptr.hpp>

#include "../../vendor/imgui/imgui.h"

#include "../../game/component/PointLightComponent.h"

ImGuiPointLightComponentAdapter::ImGuiPointLightComponentAdapter(PointLightComponent& pointLightComponent)
	: m_PointLightComponent(pointLightComponent)
{
}

void ImGuiPointLightComponentAdapter::Render() const
{
	if (m_PointLightComponent.GetPointLight())
	{
		ImGui::SliderFloat3("Ambient Color", glm::value_ptr(m_PointLightComponent.GetPointLight()->GetAmbientColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat3("Diffuse Color", glm::value_ptr(m_PointLightComponent.GetPointLight()->GetDiffuseColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat3("Specular Color", glm::value_ptr(m_PointLightComponent.GetPointLight()->GetSpecularColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat("Constant", &m_PointLightComponent.GetPointLight()->GetAttenuationReference().constant, 0.0f, 2.0f);
		ImGui::SliderFloat("Linear", &m_PointLightComponent.GetPointLight()->GetAttenuationReference().linear, 0.0f, 2.0f);
		ImGui::SliderFloat("Quadratic", &m_PointLightComponent.GetPointLight()->GetAttenuationReference().quadratic, 0.0f, 2.0f);
	}
}
