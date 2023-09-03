#pragma once

class Actor;
class ApplicationManager;
class AssetManager;
class GameManager;
class Object;
class World;

class ImGuiWorldTool
{
public:
	ImGuiWorldTool(ApplicationManager& applicationManager, AssetManager& assetManager, GameManager& gameManager);

	void Render();

private:
	void RenderLoadedWorldCombo();
	void RenderLoadedWorldComboOption(World& world);

	void RenderActorsTree();
	void RenderActorTree(Actor& actor);

	bool IsWorldLoaded(const World& world) const;
	bool IsObjectSelected(const Object& object) const;

	ApplicationManager& m_ApplicationManager;
	AssetManager& m_AssetManager;
	GameManager& m_GameManager;
};
