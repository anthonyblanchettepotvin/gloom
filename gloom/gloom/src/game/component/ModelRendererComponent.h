#pragma once

#include "RendererComponent.h"

class Model;

class ModelRendererComponent : public RendererComponent
{
public:
	ModelRendererComponent(GraphicsEngine& graphicsEngine, Model* model);

	void Render(const Camera& camera) override;

	const Model* GetModel() const { return m_Model; }

private:
	Model* m_Model = nullptr;
};
