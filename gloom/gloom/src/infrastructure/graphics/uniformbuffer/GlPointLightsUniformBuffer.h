#pragma once

#include "GlUniformBuffer.h"
#include "GlUniformBufferDataTypes.h"

class PointLight;

class GlPointLightsUniformBuffer : public GlUniformBuffer
{
public:
	GlPointLightsUniformBuffer();

	void SetPointLight(const PointLight& pointLight);

protected:
	void Send() override;

	unsigned int GetUniformBufferSize() const override;

private:
	const PointLight* m_PointLight{ nullptr }; // TODO: Support multiple point lights.

	GlUniformBufferDataPointLight m_PointLightData;
};
