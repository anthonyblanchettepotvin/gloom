#pragma once

#include <string>
#include <vector>

typedef size_t EntryIndex;

enum LogLevel;

struct LogEntry;

class Log;

class Logger
{
public:
	Logger(const std::string& key, Log& log);

	void LogMessage(LogLevel logLevel, const std::string& message);

	std::string GetKey() const { return m_Key; }

	LogEntry GetEntry(EntryIndex entryIndex) const;
	std::vector<LogEntry> GetEntries(int flags) const;

	size_t GetEntryCount() const { return m_EntriesIndexInLog.size(); }

private:
	const std::string m_Key;

	Log& m_Log;

	std::vector<EntryIndex> m_EntriesIndexInLog;
};
