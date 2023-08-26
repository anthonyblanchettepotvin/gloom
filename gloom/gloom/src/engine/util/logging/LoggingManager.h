#pragma once

#include <string>
#include <unordered_map>

#include "Log.h"

class Logger;

class LoggingManager
{
public:
	Logger& GetOrCreateLogger(const std::string& key);

	const Log& GetLog() { return m_Log; }

private:
	std::unordered_map<std::string, Logger> m_Loggers;

	Log m_Log;
};
