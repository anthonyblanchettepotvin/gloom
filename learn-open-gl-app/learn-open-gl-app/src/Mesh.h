#pragma once

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

#include <vector>

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);

	void Draw(Shader& shader);

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	void SetupMesh();
};
