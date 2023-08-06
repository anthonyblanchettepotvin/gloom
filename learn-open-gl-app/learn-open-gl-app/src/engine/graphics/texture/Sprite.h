#pragma once

#include <glm/glm.hpp>

#include "../../../engine/graphics/material/Material.h"
#include "../../../game/asset/shader/Shader.h"

class Sprite
{
public:
	Sprite(Material* material);

	virtual void Render(const glm::mat4& transform) = 0;

protected:
	Material* m_Material;
};
