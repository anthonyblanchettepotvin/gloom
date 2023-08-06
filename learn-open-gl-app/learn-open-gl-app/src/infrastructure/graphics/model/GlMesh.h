#pragma once

#include <vector>

#include "../../../engine/graphics/model/Mesh.h"

class GlMesh : public Mesh
{
public:
	GlMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Material* material);

	void Render(const glm::mat4& transform, const glm::mat3& normal) override;

private:
	unsigned int m_Vao;
	unsigned int m_Vbo;
	unsigned int m_Ebo;

	void SetupMesh();
};
