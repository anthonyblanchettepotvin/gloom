#pragma once

#include <vector>

#include "../../engine/graphics/rendering/primitive/Mesh.h"
#include "../../engine/graphics/rendering/GraphicsObject.h"

#include "../../game/asset/model/Model.h"

#include "RendererComponent.h"

class ModelRendererComponent : public RendererComponent
{
public:
	ModelRendererComponent(GraphicsEngine& graphicsEngine, Model* model);

	Model* GetModel() const { return m_Model; };

	void Render() override;

private:
	Model* m_Model;

	std::vector<GraphicsObject*> m_GraphicsObjects;
};
