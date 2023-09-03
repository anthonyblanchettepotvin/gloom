#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#include "../../EngineHelpers.h"

typedef size_t EntryIndex;

enum LogLevel
{
	ERROR = 1,
	INFO = 2,
	WARNING = 4,
};

constexpr const char* LogLevelToString(LogLevel logLevel)
{
	switch (logLevel)
	{
	case LogLevel::ERROR:
		return "ERROR";
	case LogLevel::INFO:
		return "INFO";
	case LogLevel::WARNING:
		return "WARNING";
	default:
		throw std::invalid_argument(ENUM_VALUE_IS_UNKNOWN);
	}
}

struct LogEntryData
{
	LogLevel LogLevel;

	std::streampos Start;
	std::streampos End;

	std::streamsize GetSize() const { return End - Start; }
};

struct LogEntry
{
	LogEntryData Data;

	std::string Text;
};

class Log
{
public:
	Log();

	EntryIndex LogMessageForKey(const std::string& key, LogLevel logLevel, const std::string& message);

	LogEntry GetEntry(EntryIndex entryIndex) const;
	std::vector<LogEntry> GetEntries(unsigned int flags) const;

	size_t GetEntryCount() const { return m_EntriesData.size(); }

private:
	std::stringbuf m_StringBuffer;
	std::ostream m_OutStream;

	std::vector<LogEntryData> m_EntriesData;
};
