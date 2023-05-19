#pragma once

#include <string>

#include "../Shader.h"

#include "ActorComponent.h"

class LightComponent : public ActorComponent
{
public:
	virtual void Register(Shader* shader, const std::string& identifier) = 0;
	virtual void Register(unsigned int& offset) = 0;
};
