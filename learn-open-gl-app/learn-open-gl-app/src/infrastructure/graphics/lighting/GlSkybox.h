#pragma once

#include "../../../engine/graphics/lighting/Skybox.h"

class GlSkybox : public Skybox
{
public:
	GlSkybox(Cubemap* cubemap);

	void Render(Shader* shader) override;

private:
	unsigned int m_Vao;
	unsigned int m_Vbo;

	void SetupMesh();
};
