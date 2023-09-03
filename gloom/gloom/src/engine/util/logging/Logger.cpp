#include "Logger.h"

#include "../../EngineHelpers.h"

#include "Log.h"

Logger::Logger(const std::string& key, Log& log)
	: m_Key(key), m_Log(log)
{
}

void Logger::LogMessage(LogLevel logLevel, const std::string& message)
{
	EntryIndex entryIndexInLog = m_Log.LogMessageForKey(m_Key, logLevel, message);

	m_EntriesIndexInLog.push_back(entryIndexInLog);
}

LogEntry Logger::GetEntry(EntryIndex entryIndex) const
{
	if (entryIndex >= m_EntriesIndexInLog.size())
	{
		throw std::out_of_range(INDEX_OUT_OF_RANGE);
	}

	EntryIndex entryIndexInLog = m_EntriesIndexInLog.at(entryIndex);

	return m_Log.GetEntry(entryIndexInLog);
}

std::vector<LogEntry> Logger::GetEntries(unsigned int flags) const
{
	std::vector<LogEntry> entries;

	for (size_t i = 0; i < GetEntryCount(); i++)
	{
		LogEntry entry = GetEntry(i);
		if (entry.Data.LogLevel & flags)
		{
			entries.push_back(entry);
		}
	}

	return entries;
}
