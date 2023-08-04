#include "Model.h"

Model::Model(const std::vector<Mesh*>& meshes)
	: m_Meshes(meshes)
{
}

void Model::Render(Shader* shader)
{
	for (const auto& mesh : m_Meshes)
	{
		if (mesh)
		{
			mesh->Render(shader);
		}
	}
}
