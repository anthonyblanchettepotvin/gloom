#include "Log.h"

#include <cassert>

#define INDEX_OUT_OF_RANGE "Index is out of range."
#define ENTRY_SECTION_SEPARATOR " | "

Log::Log()
	: m_OutStream(&m_StringBuffer)
{
}

EntryIndex Log::LogMessageForKey(const std::string& key, LogLevel logLevel, const std::string& message)
{
	std::streampos entryStart = m_OutStream.tellp();

	m_OutStream << __TIME__ // TODO: Log with current time instead of time at compilation.
		<< ENTRY_SECTION_SEPARATOR << LogLevelToString(logLevel) 
		<< ENTRY_SECTION_SEPARATOR << key
		<< ENTRY_SECTION_SEPARATOR << message
		<< std::endl;

	std::streampos entryEnd = m_OutStream.tellp();

	m_EntriesData.emplace_back(LogEntryData{ logLevel, entryStart, entryEnd });

	return m_EntriesData.size() - 1;
}

LogEntry Log::GetEntry(EntryIndex entryIndex) const
{
	if (entryIndex >= m_EntriesData.size())
	{
		throw std::out_of_range(INDEX_OUT_OF_RANGE);
	}

	std::streambuf* buffer = m_OutStream.rdbuf();

	assert(buffer != nullptr);

	LogEntryData entryData = m_EntriesData.at(entryIndex);

	std::string entry(entryData.GetSize(), NULL);

	buffer->pubseekpos(entryData.Start);
	buffer->sgetn(&entry[0], entryData.GetSize());
	buffer->pubseekoff(0, std::ios::end);

	return LogEntry{ entry, entryData };
}

std::vector<LogEntry> Log::GetEntries(int flags) const
{
	std::vector<LogEntry> entries;

	for (size_t i = 0; i < GetEntryCount(); i++)
	{
		auto entry = GetEntry(i);
		if (entry.Data.LogLevel & flags)
		{
			entries.push_back(entry);
		}
	}

	return entries;
}
