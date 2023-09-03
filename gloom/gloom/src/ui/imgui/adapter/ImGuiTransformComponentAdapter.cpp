#include "ImGuiTransformComponentAdapter.h"

#include <glm/gtc/type_ptr.hpp>

#include "../../../vendor/imgui/imgui.h"

#include "../../../game/component/TransformComponent.h"

ImGuiTransformComponentAdapter::ImGuiTransformComponentAdapter(TransformComponent& transformComponent)
	: m_TransformComponent(transformComponent)
{
}

void ImGuiTransformComponentAdapter::Render()
{
	ImGui::InputFloat3("Translation", glm::value_ptr(m_TransformComponent.GetTranslation()));
	ImGui::InputFloat3("Scale", glm::value_ptr(m_TransformComponent.GetScale()));
	ImGui::InputFloat3("Rotation", glm::value_ptr(m_TransformComponent.GetRotation()));
}
