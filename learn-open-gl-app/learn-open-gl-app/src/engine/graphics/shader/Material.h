#pragma once

#include "Shader.h"

class Material
{
public:
	virtual void Use(Shader* shader) = 0;
};
