#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "../../../engine/graphics/rendering/Mesh.h"

#include "../Asset.h"

class Model : public Asset
{
public:
	Model(const std::vector<Mesh*>& meshes);

	void SetTransform(const glm::mat4& transform);
	void SetMaterial(Material* material);

	std::vector<Mesh*> GetMeshes() const { return m_Meshes; }

private:
	std::vector<Mesh*> m_Meshes;
};
