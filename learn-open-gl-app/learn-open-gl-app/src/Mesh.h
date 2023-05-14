#pragma once

#include "Vertex.h"
#include "Shader.h"
#include "Material.h"

#include <vector>

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
