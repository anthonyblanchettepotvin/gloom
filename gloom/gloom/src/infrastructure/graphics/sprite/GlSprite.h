#pragma once

class Sprite;

class GlSprite
{
public:
	GlSprite(const Sprite& sprite);

	void Render();

private:
	void Initialize();

	const Sprite& m_Sprite;

	unsigned int m_Vao;
	unsigned int m_Vbo;
};
