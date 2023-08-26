#pragma once

#include <memory>

#include "util/logging/Logger.h"
#include "util/logging/LoggingManager.h"

#define DEFAULT_LOGGER_KEY typeid(this).name()

#define gLogMessageForKey(key, logLevel, message) EngineGlobals::GetInstance().GetLoggingManager().GetOrCreateLogger(key).LogMessage(logLevel, message)
#define gLogMessage(logLevel, message) gLogMessageForKey(DEFAULT_LOGGER_KEY, logLevel, message)

#define gLogErrorMessageForKey(key, message) gLogMessageForKey(key, LogLevel::ERROR, message)
#define gLogErrorMessage(message) gLogMessage(LogLevel::ERROR, message)

#define gLogInfoMessageForKey(key, message) gLogMessageForKey(key, LogLevel::INFO, message)
#define gLogInfoMessage(message) gLogMessage(LogLevel::INFO, message)

#define gLogWarningMessageForKey(key, message) gLogMessageForKey(key, LogLevel::WARNING, message)
#define gLogWarningMessage(message) gLogMessage(LogLevel::WARNING, message)

class EngineGlobalsInstance
{
public:
	EngineGlobalsInstance(LoggingManager& loggingManager);

	LoggingManager& GetLoggingManager() const { return m_LoggingManager; }

private:
	LoggingManager& m_LoggingManager;
};

class EngineGlobals
{
public:
	static void SetInstance(std::unique_ptr<EngineGlobalsInstance>& instance);
	static const EngineGlobalsInstance& GetInstance();

private:
	static std::unique_ptr<EngineGlobalsInstance> m_Instance;
};
