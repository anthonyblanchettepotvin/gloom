#include "LoggingManager.h"

#include "Logger.h"
#include "LoggerRepository.h"

LoggingManager::LoggingManager(LoggerRepository& loggerRepository)
    : m_LoggerRepository(loggerRepository)
{
}

void LoggingManager::LogMessage(const std::string& key, LogLevel logLevel, const std::string& message)
{
    Logger& logger = GetOrCreateLogger(key);

    logger.LogMessage(logLevel, message);
}

std::vector<std::string> LoggingManager::GetKeys() const
{
    return m_LoggerRepository.GetKeys();
}

std::vector<LogEntry> LoggingManager::GetLogEntries(int flags) const
{
    return m_Log.GetEntries(flags);
}

std::vector<LogEntry> LoggingManager::GetLogEntriesByKey(const std::string& key, int flags) const
{
    const Logger& logger = m_LoggerRepository.GetLogger(key);

    return logger.GetEntries(flags);
}

Logger& LoggingManager::GetOrCreateLogger(const std::string& key)
{
    if (m_LoggerRepository.DoesLoggerExists(key))
    {
        return m_LoggerRepository.GetLogger(key);
    }

    std::unique_ptr<Logger> logger = std::make_unique<Logger>(key, m_Log);
    Logger* loggerPtr = logger.get(); // Retrieve the raw pointer before the ownership is transferred to the repository.

    m_LoggerRepository.Insert(logger);

    return *loggerPtr;
}
