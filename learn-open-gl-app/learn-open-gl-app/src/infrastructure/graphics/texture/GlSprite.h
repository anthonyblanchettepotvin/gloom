#pragma once

#include "../../../engine/graphics/texture/Sprite.h"
#include "../../../engine/graphics/rendering/GraphicsObject.h"

class GlSprite : public GraphicsObject
{
public:
	GlSprite(const Sprite& sprite);

	void Render() override;

private:
	const Sprite& m_Sprite;

	unsigned int m_Vao;
	unsigned int m_Vbo;

	void Initialize();
};
