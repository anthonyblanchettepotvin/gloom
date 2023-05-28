#include "ImGuiOpenGLSettingsComponentAdapter.h"

#include "../../vendor/imgui/imgui.h"

ImGuiOpenGLSettingsComponentAdapter::ImGuiOpenGLSettingsComponentAdapter(OpenGLSettingsComponent* component)
	: UiComponentAdapter(component)
{
}

void ImGuiOpenGLSettingsComponentAdapter::RenderUi() const
{
	if (OpenGLSettingsComponent* castedComponent = dynamic_cast<OpenGLSettingsComponent*>(component))
	{
		ImGui::Checkbox("Depth testing enabled", &castedComponent->GetDepthTestingEnabledReference());
		const char* depthFunctionsName[] = { "Always", "Never", "Less", "Equal", "L. Equal", "Greater", "Not Equal", "G. Equal" };
		ImGui::Combo("Depth function", (int*)&castedComponent->GetDepthFunctionReference(), depthFunctionsName, (int)OpenGLDepthFunction::COUNT);
	}
}
