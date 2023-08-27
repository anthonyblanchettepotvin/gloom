#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Logger;

class LoggerRepository
{
public:
	void Insert(std::unique_ptr<Logger>& logger);

	std::vector<std::string> GetKeys() const;

	Logger& GetLogger(const std::string& key);
	const Logger& GetLogger(const std::string& key) const;

	bool DoesLoggerExists(const std::string& key) const;

private:
	std::unordered_map<std::string, std::unique_ptr<Logger>> m_KeyToLoggerMapping;
};
