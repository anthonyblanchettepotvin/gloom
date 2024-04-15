#pragma once

#include "GlGlobalData.h"
#include "GlGlobalDataTypes.h"

class DirectionalLight;

class GlDirectionalLightsUniformBuffer : public GlGlobalData
{
public:
	GlDirectionalLightsUniformBuffer();

	void SetDirectionalLight(const DirectionalLight& directionalLight);

protected:
	void Send() override;

	unsigned int GetUniformBufferSize() const override;

private:
	const DirectionalLight* m_DirectionalLight{ nullptr }; // TODO: Support multiple directional lights.

	GlGlobalDataDirectionalLight m_DirectionalLightData;
};
