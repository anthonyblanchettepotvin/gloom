#include "ImGuiPointLightComponentAdapter.h"

#include "../../imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

ImGuiPointLightComponentAdapter::ImGuiPointLightComponentAdapter(PointLightComponent* component)
	: UiComponentAdapter(component)
{
}

void ImGuiPointLightComponentAdapter::RenderUi() const
{
	if (PointLightComponent* castedComponent = dynamic_cast<PointLightComponent*>(component))
	{
		ImGui::SliderFloat3("Ambient Color", glm::value_ptr(castedComponent->GetAmbientColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat3("Diffuse Color", glm::value_ptr(castedComponent->GetDiffuseColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat3("Specular Color", glm::value_ptr(castedComponent->GetSpecularColorReference()), 0.0f, 1.0f);
		ImGui::SliderFloat("Constant", &castedComponent->GetLightAttenuationReference().constant, 0.0f, 2.0f);
		ImGui::SliderFloat("Linear", &castedComponent->GetLightAttenuationReference().linear, 0.0f, 2.0f);
		ImGui::SliderFloat("Quadratic", &castedComponent->GetLightAttenuationReference().quadratic, 0.0f, 2.0f);
	}
}
