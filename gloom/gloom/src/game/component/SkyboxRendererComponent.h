#pragma once

#include "RendererComponent.h"

class Skybox;

class SkyboxRendererComponent : public RendererComponent
{
public:
	SkyboxRendererComponent(GraphicsEngine& graphicsEngine, Skybox* skybox);

	void Render() override;

	const Skybox* GetSkybox() const { return m_Skybox; }

private:
	Skybox* m_Skybox = nullptr;
};
