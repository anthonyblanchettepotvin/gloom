#pragma once

#include "../../game/asset/model/Model.h"

#include "RendererComponent.h"

class ModelRendererComponent : public RendererComponent
{
public:
	ModelRendererComponent(Model* model);

	Model* GetModel() { return model; };

	void Render() override;

private:
	Model* model;
};

