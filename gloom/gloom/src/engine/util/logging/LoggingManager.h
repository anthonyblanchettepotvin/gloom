#pragma once

#include <string>
#include <unordered_map>

#include "Log.h"

class Logger;

class LoggingManager
{
public:
	Logger& GetOrCreateLogger(const std::string& key);

	std::vector<Logger> GetLoggers() const;

	const Log& GetLog() const { return m_Log; }

private:
	std::unordered_map<std::string, Logger> m_KeyToLoggerMapping;

	Log m_Log;
};
