#pragma once

class GlShader;
class GlTexture;

class GlRenderSurface
{
public:
	GlRenderSurface();

	void RenderTexture(GlShader& shader, GlTexture& texture);

private:
	void SetupSurface();

	unsigned int m_Vao;
	unsigned int m_Vbo;
};
