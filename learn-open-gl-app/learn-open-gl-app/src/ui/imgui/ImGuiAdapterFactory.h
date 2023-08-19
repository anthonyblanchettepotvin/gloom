#pragma once

class GraphicsEngine;
class ImGuiAdapter;
class Object;

class ImGuiAdapterFactory
{
public:
	ImGuiAdapterFactory(GraphicsEngine& graphicsEngine);

	ImGuiAdapter* CreateAdapter(Object* object) const;

private:
	GraphicsEngine& m_GraphicsEngine;
};
