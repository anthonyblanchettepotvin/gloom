#include "ImGuiModelRendererComponentAdapter.h"

#include "../../imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

ImGuiModelRendererComponentAdapter::ImGuiModelRendererComponentAdapter(ModelRendererComponent* component)
	: UiComponentAdapter(component)
{
}

void ImGuiModelRendererComponentAdapter::RenderUi() const
{
	if (ModelRendererComponent* castedComponent = dynamic_cast<ModelRendererComponent*>(component))
	{
		ImGui::Text(castedComponent->GetModel()->GetPath().c_str());
		ImGui::Text(castedComponent->GetShader()->GetVertexShaderPath().c_str());
		ImGui::Text(castedComponent->GetShader()->GetFragmentShaderPath().c_str());
	}
}
