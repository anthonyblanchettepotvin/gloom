#include "ImGuiSpriteRendererComponentAdapter.h"

#include "../../vendor/imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

ImGuiSpriteRendererComponentAdapter::ImGuiSpriteRendererComponentAdapter(SpriteRendererComponent* component)
	: UiComponentAdapter(component)
{
}

void ImGuiSpriteRendererComponentAdapter::RenderUi() const
{
	if (SpriteRendererComponent* castedComponent = dynamic_cast<SpriteRendererComponent*>(component))
	{
		ImGui::Text(castedComponent->GetShader()->GetVertexShaderPath().c_str());
		ImGui::Text(castedComponent->GetShader()->GetFragmentShaderPath().c_str());
	}
}
