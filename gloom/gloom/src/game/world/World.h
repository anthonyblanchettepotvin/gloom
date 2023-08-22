#pragma once

#include <vector>

#include "../../engine/object/Object.h"

class Actor;

class World : public Object
{
public:
	void SpawnActor(Actor& actor);

	std::vector<Actor*> GetActors() { return m_Actors; }

private:
	std::vector<Actor*> m_Actors;
};
