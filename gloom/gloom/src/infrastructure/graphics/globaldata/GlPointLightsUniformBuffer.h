#pragma once

#include "GlGlobalData.h"
#include "GlGlobalDataTypes.h"

class PointLight;

class GlPointLightsUniformBuffer : public GlGlobalData
{
public:
	GlPointLightsUniformBuffer();

	void SetPointLight(const PointLight& pointLight);

protected:
	void Send() override;

	unsigned int GetUniformBufferSize() const override;

private:
	const PointLight* m_PointLight{ nullptr }; // TODO: Support multiple point lights.

	GlGlobalDataPointLight m_PointLightData;
};
