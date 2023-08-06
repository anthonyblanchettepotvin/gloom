#pragma once

#include "../../engine/graphics/rendering/primitive/Skybox.h"
#include "../../engine/graphics/rendering/GraphicsObject.h"

#include "RendererComponent.h"

class SkyboxRendererComponent : public RendererComponent
{
public:
	SkyboxRendererComponent(GraphicsEngine& graphicsEngine, Skybox* skybox);

	Skybox* GetSkybox() const { return m_Skybox; }

	void Render() override;

private:
	Skybox* m_Skybox;

	GraphicsObject* m_GraphicsObject = nullptr;
};
