#pragma once

#include "../../../engine/graphics/skybox/Skybox.h"

class GlSkybox
{
public:
	GlSkybox(const Skybox& skybox);

	void Render();

private:
	const Skybox& m_Skybox;

	unsigned int m_Vao;
	unsigned int m_Vbo;

	void Initialize();
};
