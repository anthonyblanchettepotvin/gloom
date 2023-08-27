#pragma once

#include <string>
#include <vector>

#include "Log.h"

class Logger;
class LoggerRepository;

class LoggingManager
{
public:
	LoggingManager(LoggerRepository& loggerRepository);

	void LogMessage(const std::string& key, LogLevel logLevel, const std::string& message);

	std::vector<std::string> GetKeys() const;

	std::vector<LogEntry> GetLogEntries(int flags) const;
	std::vector<LogEntry> GetLogEntriesByKey(const std::string& key, int flags) const;

private:
	LoggerRepository& m_LoggerRepository;

	Log m_Log;

	Logger& GetOrCreateLogger(const std::string& key);
};
