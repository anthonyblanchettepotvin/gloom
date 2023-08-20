#include "ImGuiMain.h"

#include "../../vendor/imgui/imgui.h"

#include "../../application/ApplicationManager.h"
#include "../../engine/asset/AssetManager.h"
#include "../../engine/graphics/engine/GraphicsEngine.h"

ImGuiMain::ImGuiMain(ApplicationManager& applicationManager, AssetManager& assetManager, GraphicsEngine& graphicsEngine)
	: m_AdapterFactory(graphicsEngine)
	, m_AssetsTool(applicationManager, assetManager)
	, m_PropertiesTool(m_AdapterFactory, applicationManager, graphicsEngine)
{
}

void ImGuiMain::Render()
{
	ImGuiStyle& style = ImGui::GetStyle();

	// Padding
	style.CellPadding = ImVec2(4, 4);
	style.FramePadding = ImVec2(6, 6);
	style.WindowPadding = ImVec2(8, 8);

	style.ItemInnerSpacing = ImVec2(4, 4);
	style.ItemSpacing = ImVec2(8, 8);

	style.GrabMinSize = 16;
	style.ScrollbarSize = 16;

	// Border
	style.ChildBorderSize = 0;
	style.FrameBorderSize = 0;
	style.PopupBorderSize = 0;
	style.TabBorderSize = 0;
	style.WindowBorderSize = 0;

	// Rounding
	style.ChildRounding = 0;
	style.FrameRounding = 0;
	style.GrabRounding = 0;
	style.PopupRounding = 0;
	style.ScrollbarRounding = 0;
	style.TabRounding = 0;
	style.WindowRounding = 0;

	// Miscellaneous
	style.SeparatorTextBorderSize = 1;

	// Color
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.03f, 0.03f, 0.04f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.06f, 0.06f, 0.08f, 1.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.20f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.18f, 0.55f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.47f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.38f, 0.10f, 0.71f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.26f, 0.06f, 0.47f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.13f, 0.03f, 0.24f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.16f, 0.16f, 0.20f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.16f, 0.16f, 0.20f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.18f, 0.55f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.16f, 0.16f, 0.47f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.26f, 0.78f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.26f, 0.78f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.29f, 0.29f, 0.86f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.16f, 0.16f, 0.20f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.18f, 0.18f, 0.55f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.16f, 0.16f, 0.47f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.16f, 0.16f, 0.20f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.38f, 0.10f, 0.71f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.06f, 0.47f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.16f, 0.16f, 0.20f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.18f, 0.18f, 0.55f, 1.00f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.16f, 0.16f, 0.47f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.16f, 0.16f, 0.20f, 1.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.18f, 0.18f, 0.55f, 1.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.16f, 0.16f, 0.47f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.20f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.38f, 0.10f, 0.71f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.26f, 0.06f, 0.47f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.24f, 0.24f, 0.29f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.67f);

	m_AssetsTool.Render();
	m_PropertiesTool.Render();
}
