#pragma once

#include "GlUniformBuffer.h"
#include "GlUniformBufferDataTypes.h"

class DirectionalLight;

class GlDirectionalLightsUniformBuffer : public GlUniformBuffer
{
public:
	GlDirectionalLightsUniformBuffer();

	void SetDirectionalLight(const DirectionalLight& directionalLight);

protected:
	void Send() override;

	unsigned int GetUniformBufferSize() const override;

private:
	const DirectionalLight* m_DirectionalLight{ nullptr }; // TODO: Support multiple directional lights.

	GlUniformBufferDataDirectionalLight m_DirectionalLightData;
};
