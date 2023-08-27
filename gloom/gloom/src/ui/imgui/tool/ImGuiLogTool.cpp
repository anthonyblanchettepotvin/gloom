#include "ImGuiLogTool.h"

#include "../../../vendor/imgui/imgui.h"

#include "../../../engine/EngineGlobals.h"

#define LOG_TOOL_NAME "Log"

#define LOG_CHILD_ID "Log"

#define SELECTED_LOGGER_COMBO_LABEL "Selected Logger"

#define LOG_LEVEL_ERROR_COLOR ImVec4(1.0f, 0.2f, 0.2f, 1.0f)
#define LOG_LEVEL_INFO_COLOR ImVec4(0.2f, 0.53f, 1.0f, 1.0f)
#define LOG_LEVEL_WARNING_COLOR ImVec4(1.0f, 0.69f, 0.2f, 1.0f)

void ImGuiLogTool::Render()
{
	ImGui::Begin(LOG_TOOL_NAME);

	RenderSelectedLoggerCombo();
	RenderDisplayOptions();
	
	ImGui::Separator();

	RenderLog();

	ImGui::End();
}

void ImGuiLogTool::RenderDisplayOptions()
{
	ImGui::SameLine();
	ImGui::Checkbox("Errors", &m_DisplayErrors);

	ImGui::SameLine();
	ImGui::Checkbox("Infos", &m_DisplayInfos);

	ImGui::SameLine();
	ImGui::Checkbox("Warnings", &m_DisplayWarnings);
}

void ImGuiLogTool::RenderSelectedLoggerCombo()
{
	ImGui::PushItemWidth(200.0f);

	if (ImGui::BeginCombo(SELECTED_LOGGER_COMBO_LABEL, m_SelectedLoggerKey.c_str()))
	{
		RenderSelectedLoggerComboAllOption();

		auto loggers = EngineGlobals::GetInstance().GetLoggingManager().GetKeys();
		for (const auto& logger : loggers)
		{
			RenderSelectedLoggerComboOption(logger);
		}

		ImGui::EndCombo();
	}
}

void ImGuiLogTool::RenderSelectedLoggerComboAllOption()
{
	if (ImGui::Selectable(SELECTED_LOGGER_COMBO_ALL_OPTION, m_SelectedLoggerKey == SELECTED_LOGGER_COMBO_ALL_OPTION))
	{
		m_SelectedLoggerKey = SELECTED_LOGGER_COMBO_ALL_OPTION;
	}
}

void ImGuiLogTool::RenderSelectedLoggerComboOption(const std::string& loggerKey)
{
	if (ImGui::Selectable(loggerKey.c_str(), m_SelectedLoggerKey == loggerKey))
	{
		m_SelectedLoggerKey = loggerKey;
	}
}

void ImGuiLogTool::RenderLog()
{
	if (ImGui::BeginChild(LOG_CHILD_ID, ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysUseWindowPadding))
	{
		int entriesFlags = GetEntriesFlags();

		auto logEntries = m_SelectedLoggerKey == SELECTED_LOGGER_COMBO_ALL_OPTION
			? EngineGlobals::GetInstance().GetLoggingManager().GetLogEntries(entriesFlags)
			: EngineGlobals::GetInstance().GetLoggingManager().GetLogEntriesByKey(m_SelectedLoggerKey, entriesFlags);

		RenderLogEntries(logEntries);

		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		{
			ImGui::SetScrollHereY(1.0f);
		}

		ImGui::EndChild();
	}
}

int ImGuiLogTool::GetEntriesFlags() const
{
	int entriesFlags = 0;

	if (m_DisplayErrors)
	{
		entriesFlags |= LogLevel::ERROR;
	}

	if (m_DisplayInfos)
	{
		entriesFlags |= LogLevel::INFO;
	}

	if (m_DisplayWarnings)
	{
		entriesFlags |= LogLevel::WARNING;
	}

	return entriesFlags;
}

void ImGuiLogTool::RenderLogEntries(const std::vector<LogEntry>& logEntries)
{
	ImGuiListClipper clipper;
	clipper.Begin(logEntries.size());
	while (clipper.Step())
	{
		for (size_t i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
		{
			auto logEntry = logEntries.at(i);

			ImGui::TextColored(LogLevelToColor(logEntry.Data.LogLevel), logEntry.Text.c_str());
		}
	}
	clipper.End();
}

constexpr ImVec4 ImGuiLogTool::LogLevelToColor(LogLevel logLevel)
{
	switch (logLevel)
	{
	case LogLevel::ERROR:
		return LOG_LEVEL_ERROR_COLOR;
	case LogLevel::INFO:
		return LOG_LEVEL_INFO_COLOR;
	case LogLevel::WARNING:
		return LOG_LEVEL_WARNING_COLOR;
	default:
		return ImGui::GetStyle().Colors[ImGuiCol_Text];
	}
}
