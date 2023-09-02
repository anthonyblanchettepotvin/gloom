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

	Logger& FindLoggerByKey(const std::string& key);
	const Logger& FindLoggerByKey(const std::string& key) const;

	bool DoesLoggerExists(const std::string& key) const;

	std::vector<std::string> GetKeys() const;

private:
	std::unordered_map<std::string, std::unique_ptr<Logger>> m_KeyToLoggerMapping;

	template<class T, class Self>
	friend T& FindLoggerByKeyImpl(Self& self, const std::string& key);
};
