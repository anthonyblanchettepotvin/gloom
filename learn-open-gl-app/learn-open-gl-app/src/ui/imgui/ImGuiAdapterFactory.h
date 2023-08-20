#pragma once

#include <memory>

class GraphicsEngine;
class ImGuiAdapter;
class Object;

class ImGuiAdapterFactory
{
public:
	ImGuiAdapterFactory(GraphicsEngine& graphicsEngine);

	std::unique_ptr<ImGuiAdapter> CreateAdapter(Object* object) const;

private:
	GraphicsEngine& m_GraphicsEngine;
};
