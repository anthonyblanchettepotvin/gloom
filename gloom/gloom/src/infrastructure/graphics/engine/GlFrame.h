#pragma once

#include <memory>

class GlShader;
class GlTexture;

class GlFrame
{
public:
	void Initialize(std::unique_ptr<GlShader>& shader);

	void RenderTexture(GlTexture& texture);

private:
	std::unique_ptr<GlShader> m_Shader = nullptr;

	unsigned int m_Vao;
	unsigned int m_Vbo;
};
