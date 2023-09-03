#pragma once

#include "ImGuiAdapterFactory.h"
#include "tool/ImGuiAssetsTool.h"
#include "tool/ImGuiLogTool.h"
#include "tool/ImGuiPropertiesTool.h"
#include "tool/ImGuiWorldTool.h"

class ApplicationManager;
class AssetManager;
class GraphicsEngine;

class ImGuiMain
{
public:
	ImGuiMain(ApplicationManager& applicationManager, AssetManager& assetManager, GameManager& gameManager, GraphicsEngine& graphicsEngine);

	void Render();

private:
	void LoadFont();

	void ApplyStyle();

	ImGuiAdapterFactory m_AdapterFactory;

	ImGuiAssetsTool m_AssetsTool;
	ImGuiLogTool m_LogTool;
	ImGuiPropertiesTool m_PropertiesTool;
	ImGuiWorldTool m_WorldTool;
};
