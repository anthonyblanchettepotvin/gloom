#pragma once

#include "../shader/GlShader.h"
#include "../texture/GlTexture.h"

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
