#pragma once

#include <string>
#include <vector>

#include <assimp/mesh.h>
#include <assimp/scene.h>

#include "Mesh.h"

#include "../shader/Shader.h"

class Model
{
public:
	Model(const std::vector<Mesh*>& meshes);

	void Draw(Shader* shader);

private:
	std::vector<Mesh*> meshes;
};
