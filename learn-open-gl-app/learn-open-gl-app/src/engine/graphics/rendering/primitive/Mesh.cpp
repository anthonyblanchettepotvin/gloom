#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Material* material)
	: m_Vertices(vertices), m_Indices(indices), m_Material(material)
{
}
