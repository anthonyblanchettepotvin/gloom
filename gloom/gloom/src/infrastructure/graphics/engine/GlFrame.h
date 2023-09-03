#pragma once

#include <memory>

class GlShader;
class GlTexture;

class GlFrame
{
public:
	GlFrame(std::unique_ptr<GlShader>& shader);

	void RenderTexture(GlTexture& texture);

private:
	void Initialize();

	std::unique_ptr<GlShader> m_Shader;

	unsigned int m_Vao;
	unsigned int m_Vbo;
};
