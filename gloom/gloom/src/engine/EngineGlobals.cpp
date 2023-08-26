#include "EngineGlobals.h"

#include <cassert>

EngineGlobalsInstance::EngineGlobalsInstance(LoggingManager& loggingManager)
	: m_LoggingManager(loggingManager)
{
}

std::unique_ptr<EngineGlobalsInstance> EngineGlobals::m_Instance;

void EngineGlobals::SetInstance(std::unique_ptr<EngineGlobalsInstance>& instance)
{
	assert(instance != nullptr);

	m_Instance = std::move(instance);
}

const EngineGlobalsInstance& EngineGlobals::GetInstance()
{
	assert(m_Instance != nullptr);

	return *m_Instance;
}
