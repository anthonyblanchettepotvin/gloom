#pragma once

#include "../../engine/graphics/lighting/PointLight.h"

#include "LightComponent.h"

class PointLightComponent : public LightComponent
{
public:
	PointLightComponent(PointLight* pointLight);

	PointLight* GetPointLight() { return pointLight; };

private:
	PointLight* pointLight;
};
