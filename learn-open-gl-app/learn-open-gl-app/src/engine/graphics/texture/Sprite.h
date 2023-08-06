#pragma once

#include <glm/glm.hpp>

#include "../../../engine/graphics/engine/GraphicsEngine.h"
#include "../../../engine/graphics/material/Material.h"

#include "../rendering/RenderingPrimitive.h"

class Sprite : public RenderingPrimitive
{
public:
	Sprite(Material* material);

	void Render(GraphicsEngine& graphicsEngine);

	void SetTransform(const glm::mat4& transform) { m_Transform = transform; }
	glm::mat4 GetTransform() const { return m_Transform; }

	Material* GetMaterial() const { return m_Material; }

protected:
	glm::mat4 m_Transform{ 0.0f };

	Material* m_Material = nullptr;
};
