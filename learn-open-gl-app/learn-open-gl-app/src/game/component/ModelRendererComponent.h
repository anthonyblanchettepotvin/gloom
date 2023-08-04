#pragma once

#include "../../game/asset/model/Model.h"
#include "../../game/asset/shader/Shader.h"

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

