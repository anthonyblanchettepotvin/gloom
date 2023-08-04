#pragma once

#include "../../../game/asset/shader/Shader.h"

class Material
{
public:
	virtual void Use(Shader* shader) = 0;
};
