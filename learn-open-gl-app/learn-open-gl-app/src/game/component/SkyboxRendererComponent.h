#pragma once

#include "../../engine/graphics/lighting/Skybox.h"
#include "../../game/asset/shader/Shader.h"

#include "RendererComponent.h"

class SkyboxRendererComponent : public RendererComponent
{
public:
	SkyboxRendererComponent(Skybox* skybox, Shader* shader);

	Skybox* GetSkybox() const { return skybox; }

	void Render() override;

private:
	Skybox* skybox;
};
