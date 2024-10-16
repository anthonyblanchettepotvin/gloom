#pragma once

#include <glm/glm.hpp>

#include "../../object/Object.h"

class Material;

class Sprite : public Object
{
public:
	Sprite(Material* material);

	void SetTransform(const glm::mat4& transform) { m_Transform = transform; }
	glm::mat4 GetTransform() const { return m_Transform; }

	Material* GetMaterial() { return m_Material; }

protected:
	glm::mat4 m_Transform{ 0.0f };

	Material* m_Material = nullptr;
};
