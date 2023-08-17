#pragma once

#include "../../vendor/imgui/imgui.h"

namespace ImGuiUtils
{
	void PushGreenButtonStyle()
	{
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.3f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.3f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.3f, 0.8f, 0.8f));
	}

	void PopGreenButtonStyle()
	{
		ImGui::PopStyleColor(3);
	}
};
