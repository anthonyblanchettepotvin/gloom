#pragma once

#include "../../../engine/graphics/texture/Sprite.h"

class GlSprite : public Sprite
{
public:
	GlSprite(Material* material);

	void Render(const glm::mat4& transform) override;

private:
	unsigned int m_Vao;
	unsigned int m_Vbo;

	void SetupMesh();
};
