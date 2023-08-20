#pragma once

#include "ImGuiAdapterFactory.h"
#include "tool/ImGuiAssetsTool.h"
#include "tool/ImGuiPropertiesTool.h"

class ApplicationManager;
class AssetManager;
class GraphicsEngine;

class ImGuiMain
{
public:
	ImGuiMain(ApplicationManager& applicationManager, AssetManager& assetManager, GraphicsEngine& graphicsEngine);

	void Render();

private:
	ImGuiAdapterFactory m_AdapterFactory;

	ImGuiAssetsTool m_AssetsTool;
	ImGuiPropertiesTool m_PropertiesTool;

	void LoadFont();
	
	void ApplyStyle();
};
