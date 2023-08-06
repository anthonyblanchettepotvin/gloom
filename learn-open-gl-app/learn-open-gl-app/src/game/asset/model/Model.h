#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "../../../engine/graphics/model/Mesh.h"

#include "../Asset.h"

class Model : public Asset
{
public:
	Model(const std::vector<Mesh*>& meshes);

	void SetMaterial(Material* material);

	void Render(const glm::mat4& transform, const glm::mat3& normal);

private:
	std::vector<Mesh*> m_Meshes;
};
