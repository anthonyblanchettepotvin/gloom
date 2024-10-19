#pragma once

#include "RendererComponent.h"

class Skybox;

class SkyboxRendererComponent : public RendererComponent
{
public:
	SkyboxRendererComponent(Skybox* skybox);

	void RegisterToScene(Scene& scene) override;
	void UnregisterFromScene(Scene& scene) override;

	const Skybox* GetSkybox() const { return m_Skybox; }

private:
	Skybox* m_Skybox = nullptr;
};
