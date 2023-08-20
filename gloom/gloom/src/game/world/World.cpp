#include "World.h"

#include "../actor/Actor.h"

void World::SpawnActor(Actor& actor)
{
	m_Actors.push_back(&actor);
}
