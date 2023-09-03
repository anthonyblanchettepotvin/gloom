#include "LoggerRepository.h"

#include <cassert>
#include <stdexcept>

#include "../../EngineHelpers.h"

#include "Logger.h"

#define LOGGER_WITH_KEY_ALREADY_EXISTS "Logger with key already exists."
#define LOGGER_WITH_KEY_NOT_FOUND "Logger with key not found."

void LoggerRepository::Insert(std::unique_ptr<Logger>& logger)
{
    if (!logger)
    {
        throw std::invalid_argument(ARGUMENT_IS_NULLPTR(logger));
    }

    std::string loggerKey = logger->GetKey();

    if (DoesLoggerExists(loggerKey))
    {
        throw std::runtime_error(LOGGER_WITH_KEY_ALREADY_EXISTS);
    }

    m_KeyToLoggerMapping.emplace(loggerKey, std::move(logger));
}

template<class T, class Self>
inline T& FindLoggerByKeyImpl(Self& self, const std::string& key)
{
    if (!self.DoesLoggerExists(key))
    {
        throw std::runtime_error(LOGGER_WITH_KEY_NOT_FOUND);
    }

    auto& logger = self.m_KeyToLoggerMapping.at(key);

    assert(logger != nullptr);

    return *logger;
}

Logger& LoggerRepository::FindLoggerByKey(const std::string& key)
{
    return FindLoggerByKeyImpl<Logger>(*this, key);
}

const Logger& LoggerRepository::FindLoggerByKey(const std::string& key) const
{
    return FindLoggerByKeyImpl<const Logger>(*this, key);
}

bool LoggerRepository::DoesLoggerExists(const std::string& key) const
{
    return m_KeyToLoggerMapping.find(key) != m_KeyToLoggerMapping.end();
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
