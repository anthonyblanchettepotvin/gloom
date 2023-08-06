#pragma once

#include "../../engine/graphics/engine/GraphicsEngine.h"

#include "ActorComponent.h"

class RendererComponent : public ActorComponent
{
public:
	RendererComponent(GraphicsEngine& graphicsEngine);

	virtual void Render() = 0;

protected:
	GraphicsEngine& m_GraphicsEngine;
};
