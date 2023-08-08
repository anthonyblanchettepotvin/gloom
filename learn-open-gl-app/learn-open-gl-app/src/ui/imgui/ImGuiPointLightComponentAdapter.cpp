#include "ImGuiPointLightComponentAdapter.h"

#include "../../vendor/imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

ImGuiPointLightComponentAdapter::ImGuiPointLightComponentAdapter(PointLightComponent* component)
	: UiComponentAdapter(component)
{
}

void ImGuiPointLightComponentAdapter::RenderUi() const
{
	if (PointLightComponent* castedComponent = dynamic_cast<PointLightComponent*>(component))
	{
		ImGui::SliderFloat3("Ambient Color", glm::value_ptr(castedComponent->GetPointLight()->GetAmbientColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat3("Diffuse Color", glm::value_ptr(castedComponent->GetPointLight()->GetDiffuseColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat3("Specular Color", glm::value_ptr(castedComponent->GetPointLight()->GetSpecularColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat("Constant", &castedComponent->GetPointLight()->GetAttenuationReference().constant, 0.0f, 2.0f);
		ImGui::SliderFloat("Linear", &castedComponent->GetPointLight()->GetAttenuationReference().linear, 0.0f, 2.0f);
		ImGui::SliderFloat("Quadratic", &castedComponent->GetPointLight()->GetAttenuationReference().quadratic, 0.0f, 2.0f);
	}
}
