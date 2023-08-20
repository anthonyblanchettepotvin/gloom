#include "ImGuiMain.h"

#include "../../vendor/imgui/imgui.h"

#include "../../application/ApplicationManager.h"
#include "../../engine/asset/AssetManager.h"
#include "../../engine/graphics/engine/GraphicsEngine.h"

#define ROBOTO_REGULAR_TTF_PATH ".\\fonts\\roboto\\Roboto-Regular.ttf"

ImGuiMain::ImGuiMain(ApplicationManager& applicationManager, AssetManager& assetManager, GraphicsEngine& graphicsEngine)
	: m_AdapterFactory(graphicsEngine)
	, m_AssetsTool(applicationManager, assetManager)
	, m_PropertiesTool(m_AdapterFactory, applicationManager, graphicsEngine)
{
	LoadFont();

	ApplyStyle();
}

void ImGuiMain::Render()
{
	m_AssetsTool.Render();
	m_PropertiesTool.Render();
}

void ImGuiMain::LoadFont()
{
	ImGuiIO& io = ImGui::GetIO();

	if (!io.Fonts)
		return;

	io.Fonts->AddFontFromFileTTF(ROBOTO_REGULAR_TTF_PATH, 16);
}

void ImGuiMain::ApplyStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();

	// Padding
	style.CellPadding = ImVec2(4, 4);
	style.FramePadding = ImVec2(6, 6);
	style.WindowPadding = ImVec2(8, 8);

	// Spacing
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.ItemSpacing = ImVec2(8, 8);

	// Size
	style.GrabMinSize = 16;
	style.ScrollbarSize = 16;

	// Border
	style.ChildBorderSize = 0;
	style.FrameBorderSize = 0;
	style.PopupBorderSize = 0;
	style.TabBorderSize = 0;
	style.WindowBorderSize = 0;

	// Rounding
	style.ChildRounding = 2;
	style.FrameRounding = 2;
	style.GrabRounding = 2;
	style.PopupRounding = 2;
	style.ScrollbarRounding = 2;
	style.TabRounding = 2;
	style.WindowRounding = 2;

	// Miscellaneous
	style.SeparatorTextBorderSize = 1;

	// Color
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.16f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.10f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.09f, 0.09f, 0.12f, 1.00f);
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
}
