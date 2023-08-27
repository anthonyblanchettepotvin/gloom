#include "LoggerRepository.h"

#include <cassert>
#include <stdexcept>

#include "Logger.h"

#define LOGGER_WITH_KEY_ALREADY_EXISTS "Logger with key already exists."
#define LOGGER_WITH_KEY_NOT_FOUND "Logger with key not found."

void LoggerRepository::Insert(std::unique_ptr<Logger>& logger)
{
    assert(logger != nullptr);

    if (DoesLoggerExists(logger->GetKey()))
    {
        throw std::runtime_error(LOGGER_WITH_KEY_ALREADY_EXISTS);
    }

    m_KeyToLoggerMapping.emplace(logger->GetKey(), std::move(logger));
}

std::vector<std::string> LoggerRepository::GetKeys() const
{
    std::vector<std::string> keys;

    for (const auto& keyToLogger : m_KeyToLoggerMapping)
    {
        keys.push_back(keyToLogger.first);
    }

    return keys;
}

Logger& LoggerRepository::GetLogger(const std::string& key)
{
    if (!DoesLoggerExists(key))
    {
        throw std::runtime_error(LOGGER_WITH_KEY_NOT_FOUND);
    }

    return *m_KeyToLoggerMapping.at(key);
}

const Logger& LoggerRepository::GetLogger(const std::string& key) const
{
    if (!DoesLoggerExists(key))
    {
        throw std::runtime_error(LOGGER_WITH_KEY_NOT_FOUND);
    }

    return *m_KeyToLoggerMapping.at(key);
}

bool LoggerRepository::DoesLoggerExists(const std::string& key) const
{
    return m_KeyToLoggerMapping.find(key) != m_KeyToLoggerMapping.end();
}
