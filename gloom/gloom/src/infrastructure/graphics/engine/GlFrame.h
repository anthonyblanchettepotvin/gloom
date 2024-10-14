#pragma once

#include <memory>

#include "../../../engine/graphics/shader/Shader.h"

#include "../shader/GlShader.h"

class GlTexture;

class GlFrame
{
public:
	GlFrame();

	void Initialize();

	void RenderTexture(GlTexture& texture);

private:
	Shader m_Shader;
	GlShader m_GlShader;

	unsigned int m_Vao = 0;
	unsigned int m_Vbo = 0;
};
