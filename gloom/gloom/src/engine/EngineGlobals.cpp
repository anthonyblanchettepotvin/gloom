#include "EngineGlobals.h"

#include <cassert>

#include "EngineHelpers.h"

std::unique_ptr<EngineGlobalsInstance> EngineGlobals::m_Instance;

EngineGlobalsInstance::EngineGlobalsInstance(LoggingManager& loggingManager)
	: m_LoggingManager(loggingManager)
{
}

void EngineGlobals::SetInstance(std::unique_ptr<EngineGlobalsInstance>& instance)
{
	if (!instance)
	{
		throw std::invalid_argument(ARGUMENT_IS_NULLPTR(instance));
	}

	m_Instance = std::move(instance);
}

EngineGlobalsInstance& EngineGlobals::GetInstance()
{
	assert(m_Instance != nullptr);

	return *m_Instance;
}
