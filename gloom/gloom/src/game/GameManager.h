#pragma once

class World;

class GameManager
{
public:
	void LoadWorld(World& world);

	World* GetLoadedWorld() const { return m_LoadedWorld; }

private:
	World* m_LoadedWorld = nullptr;
};
