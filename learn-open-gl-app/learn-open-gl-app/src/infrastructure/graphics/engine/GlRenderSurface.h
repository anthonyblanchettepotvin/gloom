#pragma once

#include "../rendering/GlTexture.h"
#include "../shader/GlShader.h"

class GlRenderSurface
{
public:
	GlRenderSurface();

	void RenderTexture(GlShader& shader, GlTexture& texture);

private:
	unsigned int m_Vao;
	unsigned int m_Vbo;

	void SetupSurface();
};
