#include "ImGuiMain.h"

#include "../../application/ApplicationManager.h"
#include "../../engine/asset/AssetManager.h"
#include "../../engine/graphics/engine/GraphicsEngine.h"

ImGuiMain::ImGuiMain(ApplicationManager& applicationManager, AssetManager& assetManager, GraphicsEngine& graphicsEngine)
	: m_AdapterFactory(graphicsEngine)
	, m_AssetsTool(applicationManager, assetManager)
	, m_PropertiesTool(m_AdapterFactory, applicationManager, graphicsEngine)
{
}

void ImGuiMain::Render()
{
	m_AssetsTool.Render();
	m_PropertiesTool.Render();
}
