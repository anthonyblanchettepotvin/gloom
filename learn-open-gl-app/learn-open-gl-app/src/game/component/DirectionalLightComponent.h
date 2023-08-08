#pragma once

#include "../../engine/graphics/lighting/DirectionalLight.h"

#include "LightComponent.h"

class DirectionalLightComponent : public LightComponent
{
public:
	DirectionalLightComponent(DirectionalLight* directionalLight);

	DirectionalLight* GetDirectionalLight() { return directionalLight; };

private:
	DirectionalLight* directionalLight;
};
