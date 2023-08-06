#pragma once

#include "ActorComponent.h"

class RendererComponent : public ActorComponent
{
public:
	virtual void Render() = 0;
};
