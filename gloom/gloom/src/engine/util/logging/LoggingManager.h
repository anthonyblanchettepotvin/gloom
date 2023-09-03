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

	std::vector<LogEntry> GetLogEntries(unsigned int flags) const;
	std::vector<LogEntry> GetLogEntriesByKey(const std::string& key, unsigned int flags) const;

	std::vector<std::string> GetKeys() const;

private:
	Logger& FindOrCreateLogger(const std::string& key);

	LoggerRepository& m_LoggerRepository;

	Log m_Log;
};
