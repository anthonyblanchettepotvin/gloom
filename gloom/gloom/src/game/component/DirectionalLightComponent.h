#pragma once

#include "LightComponent.h"

class DirectionalLight;

class DirectionalLightComponent : public LightComponent
{
public:
	DirectionalLightComponent(DirectionalLight* directionalLight);

	void OnParentSpawned() override;

	DirectionalLight* GetDirectionalLight() { return m_DirectionalLight; }

private:
	DirectionalLight* m_DirectionalLight = nullptr;
};
