#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "../material/Material.h"

#include "Vertex.h"

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Material* material);

	void SetMaterial(Material* material) { m_Material = material; }

	virtual void Render(const glm::mat4& transform, const glm::mat3& normal) = 0;

protected:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

	Material* m_Material;
};
