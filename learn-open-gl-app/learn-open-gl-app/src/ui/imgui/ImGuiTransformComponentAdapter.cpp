#include "ImGuiTransformComponentAdapter.h"

#include <glm/gtc/type_ptr.hpp>

#include "../../vendor/imgui/imgui.h"

#include "../../game/component/TransformComponent.h"

ImGuiTransformComponentAdapter::ImGuiTransformComponentAdapter(TransformComponent& transformComponent)
	: m_TransformComponent(transformComponent)
{
}

void ImGuiTransformComponentAdapter::Render() const
{
	ImGui::InputFloat3("Position", glm::value_ptr(m_TransformComponent.GetPositionReference()));
	ImGui::InputFloat3("Scale", glm::value_ptr(m_TransformComponent.GetScaleReference()));
	ImGui::InputFloat3("Rotation", glm::value_ptr(m_TransformComponent.GetRotationReference()));
}
