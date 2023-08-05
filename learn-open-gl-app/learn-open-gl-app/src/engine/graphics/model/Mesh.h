#pragma once

#include <vector>

#include "Vertex.h"

#include "../shader/Material.h"
#include "../../../game/asset/shader/Shader.h"

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Material* material);

	virtual void Render(Shader* shader) = 0;

protected:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Material* material;
};
