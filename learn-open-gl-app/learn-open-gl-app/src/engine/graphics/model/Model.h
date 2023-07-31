#pragma once

#include <vector>

#include "Mesh.h"
#include "../shader/Shader.h"

class Model
{
public:
	Model(const std::vector<Mesh*>& meshes);

	void Render(Shader* shader);

private:
	std::vector<Mesh*> meshes;
};
