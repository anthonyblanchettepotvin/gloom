#pragma once

#include "../../engine/graphics/shader/Shader.h"

#include "ActorComponent.h"

class RendererComponent : public ActorComponent
{
public:
	RendererComponent(Shader* shader);

	Shader* GetShader() { return shader; };

	virtual void Render() = 0;

protected:
	Shader* shader;
};
