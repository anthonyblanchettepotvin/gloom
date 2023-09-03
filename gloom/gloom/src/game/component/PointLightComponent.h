#pragma once

#include "LightComponent.h"

class PointLight;

class PointLightComponent : public LightComponent
{
public:
	PointLightComponent(PointLight* pointLight);

	PointLight* GetPointLight() { return m_PointLight; }

private:
	PointLight* m_PointLight = nullptr;
};
