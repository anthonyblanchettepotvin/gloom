#pragma once

#include <vector>

#include "Vertex.h"

#include "../shader/Shader.h"
#include "../shader/Material.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	Material* material;
	
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Material* material);

	void Draw(Shader* shader);

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	void SetupMesh();
};
