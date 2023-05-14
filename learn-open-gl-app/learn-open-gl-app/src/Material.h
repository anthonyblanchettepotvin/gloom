#pragma once

#include "Shader.h"

class Material
{
public:
	virtual void Bind(Shader* shader) = 0;
};
