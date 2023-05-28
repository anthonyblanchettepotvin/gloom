#include "Model.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model::Model(const std::vector<Mesh*>& meshes)
	: meshes(meshes)
{
}

void Model::Draw(Shader* shader)
{
	for (const auto& mesh : meshes)
	{
		if (mesh)
		{
			mesh->Draw(shader);
		}
	}
}
