#include "World.h"

void World::SpawnActor(Actor* actor)
{
	actors.push_back(actor);
}

std::vector<std::string> World::GetActorsName()
{
	std::vector<std::string> actorsName;

	for (auto actor : actors)
	{
		actorsName.push_back(actor->GetName());
	}

	return actorsName;
}
