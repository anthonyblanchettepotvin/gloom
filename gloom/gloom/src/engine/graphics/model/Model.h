#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "../../object/Object.h"

#include "../mesh/Mesh.h"

class Material;

class Model : public Object
{
public:
	Model() = default;
	Model(std::vector<std::unique_ptr<Mesh>>& meshes);

	void SetTransform(const glm::mat4& transform);
	void SetMaterial(Material* material);

	std::vector<Mesh*> GetMeshes();

private:
	std::vector<std::unique_ptr<Mesh>> m_Meshes;
};
