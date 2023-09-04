#pragma once

class Actor;
class ApplicationManager;
class Asset;
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
	void RenderLoadedWorldComboOption(Asset& world);

	void RenderActorsTree();
	void RenderActorTree(Actor& actor);

	ApplicationManager& m_ApplicationManager;
	AssetManager& m_AssetManager;
	GameManager& m_GameManager;
};
