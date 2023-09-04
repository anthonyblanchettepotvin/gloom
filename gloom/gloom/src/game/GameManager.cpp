#include "GameManager.h"

void GameManager::LoadWorld(World* world)
{
	m_LoadedWorld = world;
}

bool GameManager::IsWorldLoaded(World* world)
{
	return m_LoadedWorld != nullptr && world != nullptr && m_LoadedWorld == world;
}
