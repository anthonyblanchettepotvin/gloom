#include "LoggingManager.h"

#include "Logger.h"

Logger& LoggingManager::GetOrCreateLogger(const std::string& key)
{
    auto it = m_KeyToLoggerMapping.find(key);
    if (it == m_KeyToLoggerMapping.end())
    {
        m_KeyToLoggerMapping.emplace(key, Logger(key, m_Log));
    }

    return m_KeyToLoggerMapping.at(key);
}

std::vector<Logger> LoggingManager::GetLoggers() const
{
    std::vector<Logger> loggers;

    for (const auto& keyToLogger : m_KeyToLoggerMapping)
    {
        loggers.emplace_back(keyToLogger.second);
    }

    return loggers;
}
