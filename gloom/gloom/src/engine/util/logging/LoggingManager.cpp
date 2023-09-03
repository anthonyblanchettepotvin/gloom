#include "LoggingManager.h"

#include "Logger.h"
#include "LoggerRepository.h"

LoggingManager::LoggingManager(LoggerRepository& loggerRepository)
    : m_LoggerRepository(loggerRepository)
{
}

void LoggingManager::LogMessage(const std::string& key, LogLevel logLevel, const std::string& message)
{
    Logger& logger = FindOrCreateLogger(key);

    logger.LogMessage(logLevel, message);
}

std::vector<std::string> LoggingManager::GetKeys() const
{
    return m_LoggerRepository.GetKeys();
}

std::vector<LogEntry> LoggingManager::GetLogEntries(unsigned int flags) const
{
    return m_Log.GetEntries(flags);
}

std::vector<LogEntry> LoggingManager::GetLogEntriesByKey(const std::string& key, unsigned int flags) const
{
    Logger& logger = m_LoggerRepository.FindLoggerByKey(key);

    return logger.GetEntries(flags);
}

Logger& LoggingManager::FindOrCreateLogger(const std::string& key)
{
    if (m_LoggerRepository.DoesLoggerExists(key))
    {
        return m_LoggerRepository.FindLoggerByKey(key);
    }

    std::unique_ptr<Logger> logger = std::make_unique<Logger>(key, m_Log);
    Logger* loggerPtr = logger.get(); // Retrieve the raw pointer before the ownership is transferred to the repository.

    m_LoggerRepository.Insert(logger);

    return *loggerPtr;
}
