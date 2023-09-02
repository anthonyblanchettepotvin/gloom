#pragma once

#include "ActorComponent.h"

class GraphicsEngine;

class RendererComponent : public ActorComponent
{
public:
	RendererComponent(GraphicsEngine& graphicsEngine);

	virtual void Render() = 0;

protected:
	GraphicsEngine& m_GraphicsEngine;
};
