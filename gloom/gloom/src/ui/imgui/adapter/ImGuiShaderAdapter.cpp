#include "ImGuiShaderAdapter.h"

#include "../../../vendor/imgui/imgui.h"

#include "../../../engine/graphics/shader/Shader.h"

ImGuiShaderAdapter::ImGuiShaderAdapter(Shader& shader)
	: m_Shader(shader)
{
}

void ImGuiShaderAdapter::Render()
{
	std::string shaderCode = m_Shader.GetCode();
	ImGui::Text(shaderCode.c_str());
}
