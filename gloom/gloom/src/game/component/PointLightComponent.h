#pragma once

#include "LightComponent.h"

class PointLight;

class PointLightComponent : public LightComponent
{
public:
	PointLightComponent(PointLight* pointLight);

	void OnParentSpawned() override;

	PointLight* GetPointLight() { return m_PointLight; }

private:
	PointLight* m_PointLight = nullptr;
};
