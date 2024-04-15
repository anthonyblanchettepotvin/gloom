#include "World.h"

#include "../../engine/EngineGlobals.h"

#include "../actor/Actor.h"

void World::SpawnActor(Actor& actor)
{
	auto it = std::find(m_Actors.begin(), m_Actors.end(), &actor);
	if (it == m_Actors.end())
	{
		m_Actors.push_back(&actor);

		actor.OnSpawned();
	}
	else
	{
		std::stringstream ss;
		ss << "Actor " << actor.GetName() << " already spawned.";
		gLogErrorMessage(ss.str());
	}
}
