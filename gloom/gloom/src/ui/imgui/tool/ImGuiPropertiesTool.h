#pragma once

class ApplicationManager;
class GraphicsEngine;
class ImGuiAdapterFactory;

class ImGuiPropertiesTool
{
public:
	ImGuiPropertiesTool(ImGuiAdapterFactory& adapterFactory, ApplicationManager& applicationManager, GraphicsEngine& graphicsEngine);

	void Render();

private:
	void RenderSelectedObjectProperties();

	ImGuiAdapterFactory& m_AdapterFactory;

	ApplicationManager& m_ApplicationManager;
	GraphicsEngine& m_GraphicsEngine;
};
