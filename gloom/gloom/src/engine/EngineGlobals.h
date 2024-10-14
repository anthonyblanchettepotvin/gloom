#pragma once

#include <memory>

#include "graphics/engine/GraphicsEngine.h"
#include "util/logging/Logger.h"
#include "util/logging/LoggingManager.h"

#define DEFAULT_LOGGER_KEY typeid(this).name()

#define gLogMessageForKey(key, logLevel, message) EngineGlobals::GetInstance().GetLoggingManager().LogMessage(key, logLevel, message)
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
	EngineGlobalsInstance(GraphicsEngine& graphicsEngine, LoggingManager& loggingManager);

	GraphicsEngine& GetGraphicsEngine() { return m_GraphicsEngine; }
	LoggingManager& GetLoggingManager() { return m_LoggingManager; }

private:
	GraphicsEngine& m_GraphicsEngine;
	LoggingManager& m_LoggingManager;
};

class EngineGlobals
{
public:
	static void SetInstance(std::unique_ptr<EngineGlobalsInstance>& instance);
	static EngineGlobalsInstance& GetInstance();

private:
	static std::unique_ptr<EngineGlobalsInstance> m_Instance;
};
