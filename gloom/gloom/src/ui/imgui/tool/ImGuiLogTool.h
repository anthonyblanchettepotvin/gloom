#pragma once

#include <string>
#include <vector>

#define SELECTED_LOGGER_COMBO_ALL_OPTION "All"

enum LogLevel;

struct ImVec4;
struct LogEntry;

class Logger;

class ImGuiLogTool
{
public:
	void Render();

private:
	std::string m_SelectedLoggerKey = SELECTED_LOGGER_COMBO_ALL_OPTION;

	bool m_DisplayErrors = true;
	bool m_DisplayInfos = true;
	bool m_DisplayWarnings = true;

	void RenderSelectedLoggerCombo();
	void RenderDisplayOptions();
	void RenderSelectedLoggerComboAllOption();
	void RenderSelectedLoggerComboOption(const std::string& loggerKey);

	void RenderLog();
	int GetEntriesFlags() const;
	void RenderLogEntries(const std::vector<LogEntry>& logEntries);
	
	static constexpr ImVec4 LogLevelToColor(LogLevel logLevel);
};
