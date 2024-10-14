#pragma once

#include "ActorComponent.h"

class Camera;
class GraphicsEngine;

class RendererComponent : public ActorComponent
{
public:
	RendererComponent(GraphicsEngine& graphicsEngine);

	virtual void Render(const Camera& camera) = 0;

protected:
	GraphicsEngine& m_GraphicsEngine;
};
