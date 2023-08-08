#pragma once

#include "../../../engine/graphics/rendering/Sprite.h"

class GlSprite
{
public:
	GlSprite(const Sprite& sprite);

	void Render();

private:
	const Sprite& m_Sprite;

	unsigned int m_Vao;
	unsigned int m_Vbo;

	void Initialize();
};
