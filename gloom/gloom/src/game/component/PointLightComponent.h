#pragma once

#include "LightComponent.h"

class PointLight;

class PointLightComponent : public LightComponent
{
public:
	PointLightComponent(PointLight* pointLight);

	void RegisterToScene(Scene& scene) override;
	void UnregisterFromScene(Scene& scene) override;

	PointLight* GetPointLight() { return m_PointLight; }

private:
	PointLight* m_PointLight = nullptr;
};
