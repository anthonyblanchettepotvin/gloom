#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "../../../engine/graphics/engine/GraphicsEngine.h"
#include "../../../engine/graphics/model/Mesh.h"

#include "../Asset.h"

class Model : public Asset
{
public:
	Model(const std::vector<Mesh*>& meshes);

	void SetTransform(const glm::mat4& transform);
	void SetMaterial(Material* material);

	void Render(GraphicsEngine& graphicsEngine);

private:
	std::vector<Mesh*> m_Meshes;
};
