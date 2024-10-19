#pragma once

#include "RendererComponent.h"

class Model;
class Scene;

class ModelRendererComponent : public RendererComponent
{
public:
	ModelRendererComponent(Model* model);

	void RegisterToScene(Scene& scene) override;
	void UnregisterFromScene(Scene& scene) override;

	const Model* GetModel() const { return m_Model; }

private:
	Model* m_Model = nullptr;
};
