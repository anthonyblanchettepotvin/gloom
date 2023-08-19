#pragma once

#include "tool/ImGuiAssetsTool.h"
#include "tool/ImGuiPropertiesTool.h"

#include "ImGuiAdapterFactory.h"

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
};
