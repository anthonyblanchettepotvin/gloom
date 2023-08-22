#include "World.h"

#include "../actor/Actor.h"

void World::SpawnActor(Actor& actor)
{
	auto it = std::find(m_Actors.begin(), m_Actors.end(), &actor);
	if (it == m_Actors.end())
	{
		m_Actors.push_back(&actor);
	}
	else
	{
		// TODO: Log error
	}
}
