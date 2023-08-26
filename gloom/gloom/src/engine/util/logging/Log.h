#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#define ENUM_VALUE_UNKNOWN "Enum value is unknown."

typedef size_t EntryIndex;

enum class LogLevel
{
	INFO,
	WARNING,
	ERROR
};

constexpr const char* LogLevelToString(LogLevel logLevel)
{
	switch (logLevel)
	{
	case LogLevel::INFO:
		return "INFO";
	case LogLevel::WARNING:
		return "WARNING";
	case LogLevel::ERROR:
		return "ERROR";
	default:
		throw std::invalid_argument(ENUM_VALUE_UNKNOWN);
	}
}

struct LogEntryData
{
	std::streampos Start;
	std::streampos End;

	std::streamsize GetSize() const { return End - Start; }
};

class Log
{
public:
	Log();

	EntryIndex LogMessageForKey(const std::string& key, LogLevel logLevel, const std::string& message);

	std::string GetEntry(EntryIndex entryIndex) const;

	size_t GetEntryCount() const { return m_EntriesData.size(); }

private:
	std::stringbuf m_StringBuffer;
	std::ostream m_OutStream;

	std::vector<LogEntryData> m_EntriesData;
};
