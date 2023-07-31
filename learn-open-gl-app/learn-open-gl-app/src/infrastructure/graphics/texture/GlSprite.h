#pragma once

#include "../../../engine/graphics/texture/Sprite.h"

class GlSprite : public Sprite
{
public:
	GlSprite(Texture* texture);

	void Render(Shader* shader) override;

private:
	unsigned int m_Vao;
	unsigned int m_Vbo;

	void SetupMesh();
};
