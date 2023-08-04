#pragma once

#include "../../../game/asset/shader/Shader.h"
#include "../../../game/asset/cubemap/Cubemap.h"

class Skybox
{
public:
	Skybox(Cubemap* cubemap);

	virtual void Render(Shader* shader) = 0;

protected:
	Cubemap* cubemap;
};
