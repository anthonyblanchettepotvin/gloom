#pragma once

#include "../../engine/graphics/model/Model.h"
#include "../../engine/graphics/shader/Shader.h"

#include "RendererComponent.h"

class ModelRendererComponent : public RendererComponent
{
public:
	ModelRendererComponent(Model* model, Shader* shader);

	Model* GetModel() { return model; };

	void Render() override;

private:
	Model* model;
};

