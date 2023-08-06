#pragma once

#include "../../../engine/graphics/lighting/Skybox.h"

class GlSkybox : public Skybox
{
public:
	GlSkybox(Material* material);

	void Render() override;

private:
	unsigned int m_Vao;
	unsigned int m_Vbo;

	void SetupMesh();
};
