#pragma once

#include <vector>

#include "../../engine/object/Object.h"
#include "../../engine/graphics/scene/Scene.h"

class Actor;

class World : public Object
{
public:
	void SpawnActor(Actor& actor);
	// TODO: void UnspawnActor(Actor& actor);

	std::vector<Actor*> GetActors() { return m_Actors; }

	Scene& GetScene() { return m_Scene; }

private:
	std::vector<Actor*> m_Actors;

	Scene m_Scene;
};
