#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "../../object/Object.h"

#include "Vertex.h"

class Material;

class Mesh : public Object
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Material* material);

	void SetTransform(const glm::mat4& transform) { m_Transform = transform; }
	glm::mat4 GetTransform() const { return m_Transform; }

	std::vector<Vertex> GetVertices() const { return m_Vertices; }

	std::vector<unsigned int> GetIndices() const { return m_Indices; }

	void SetMaterial(Material* material) { m_Material = material; }
	Material* GetMaterial() { return m_Material; }

protected:
	glm::mat4 m_Transform{ 0.0f };

	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

	Material* m_Material = nullptr;
};
