#include "Model.h"

Model::Model(const std::vector<Mesh*>& meshes)
	: m_Meshes(meshes)
{
}

void Model::SetTransform(const glm::mat4& transform)
{
	for (const auto& mesh : m_Meshes)
	{
		if (mesh)
		{
			mesh->SetTransform(transform);
		}
	}
}

void Model::SetMaterial(Material* material)
{
	for (const auto& mesh : m_Meshes)
	{
		if (mesh)
		{
			mesh->SetMaterial(material);
		}
	}
}
