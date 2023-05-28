#include "ImGuiTransformComponentAdapter.h"

#include "../../vendor/imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

ImGuiTransformComponentAdapter::ImGuiTransformComponentAdapter(TransformComponent* component)
	: UiComponentAdapter(component)
{
}

void ImGuiTransformComponentAdapter::RenderUi() const
{
	if (TransformComponent* castedComponent = dynamic_cast<TransformComponent*>(component))
	{
		ImGui::InputFloat3("Position", glm::value_ptr(castedComponent->GetPositionReference()));
		ImGui::InputFloat3("Scale", glm::value_ptr(castedComponent->GetScaleReference()));
		ImGui::InputFloat3("Rotation", glm::value_ptr(castedComponent->GetRotationReference()));
	}
}
