#include "LoggingManager.h"

#include "Logger.h"

Logger& LoggingManager::GetOrCreateLogger(const std::string& key)
{
    auto it = m_Loggers.find(key);
    if (it == m_Loggers.end())
    {
        m_Loggers.emplace(key, Logger(key, m_Log));
    }

    return m_Loggers.at(key);
}
