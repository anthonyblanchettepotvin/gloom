#pragma once

#include <vector>

#include "../../engine/object/Object.h"

class Actor;

class World : public Object
{
public:
	void SpawnActor(Actor* actor);

	std::vector<Actor*> GetActors() { return actors; };
	std::vector<std::string> GetActorsName();

private:
	std::vector<Actor*> actors;
};
