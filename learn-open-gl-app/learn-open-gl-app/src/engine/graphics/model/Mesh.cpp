#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Material* material)
	: vertices(vertices), indices(indices), material(material)
{
}
