#include "Model.h"

Model::Model(const std::vector<Mesh*>& meshes)
	: m_Meshes(meshes)
{
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

void Model::Render(const glm::mat4& transform, const glm::mat3& normal)
{
	for (const auto& mesh : m_Meshes)
	{
		if (mesh)
		{
			mesh->Render(transform, normal);
		}
	}
}
