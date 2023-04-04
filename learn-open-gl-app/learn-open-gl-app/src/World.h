#pragma once

#include <vector>

#include "Actor.h"

class World
{
public:
	void SpawnActor(Actor* actor);

	std::vector<Actor*> GetActors() { return actors; };
	std::vector<std::string> GetActorsName();

private:
	std::vector<Actor*> actors;
};
