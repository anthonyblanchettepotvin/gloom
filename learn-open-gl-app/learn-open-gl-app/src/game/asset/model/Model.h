#pragma once

#include <vector>

#include "../../../engine/graphics/model/Mesh.h"
#include "../../../game/asset/shader/Shader.h"

#include "../Asset.h"

class Model : public Asset
{
public:
	Model(const std::vector<Mesh*>& meshes);

	void Render(Shader* shader);

private:
	std::vector<Mesh*> m_Meshes;
};
