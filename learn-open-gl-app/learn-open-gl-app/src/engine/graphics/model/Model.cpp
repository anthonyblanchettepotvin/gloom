#include "Model.h"

Model::Model(const std::vector<Mesh*>& meshes)
	: meshes(meshes)
{
}

void Model::Render(Shader* shader)
{
	for (const auto& mesh : meshes)
	{
		if (mesh)
		{
			mesh->Render(shader);
		}
	}
}
