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
	ApplicationManager& m_ApplicationManager;
	AssetManager& m_AssetManager;
	GameManager& m_GameManager;

	void RenderLoadedWorldCombo();
	void RenderLoadedWorldComboOption(World& world);
	bool IsWorldLoaded(const World& world) const;

	void RenderActorsTree();
	void RenderActorTree(Actor& actor);
	bool IsObjectSelected(const Object& object) const;
};
