#include "GameManager.h"

void GameManager::LoadWorld(World& world)
{
	if (m_LoadedWorld == &world)
		return;

	m_LoadedWorld = &world;
}
