#include "Model.h"

#include <cassert>
#include <stdexcept>

#include "../../EngineHelpers.h"

#include "../mesh/Mesh.h"

Model::Model(std::vector<std::unique_ptr<Mesh>>& meshes)
{
	for (const auto& mesh : meshes)
	{
		if (!mesh)
		{
			throw std::invalid_argument(ARGUMENT_CONTAINS_NULLPTR(meshes));
		}
	}

	m_Meshes = std::move(meshes);
}

void Model::SetTransform(const glm::mat4& transform)
{
	for (const auto& mesh : m_Meshes)
	{
		assert(mesh != nullptr);

		mesh->SetTransform(transform);
	}
}

void Model::SetMaterial(Material* material)
{
	for (const auto& mesh : m_Meshes)
	{
		assert(mesh != nullptr);
		
		mesh->SetMaterial(material);
	}
}

std::vector<Mesh*> Model::GetMeshes()
{
	std::vector<Mesh*> result;

	for (const auto& mesh : m_Meshes)
	{
		assert(mesh != nullptr);

		result.push_back(mesh.get());
	}

	return result;
}
