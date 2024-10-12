#include "GlPointLightsUniformBuffer.h"

#include "../../../engine/graphics/lighting/PointLight.h"

#include "../engine/GlGraphicsEngine.h"

GlPointLightsUniformBuffer::GlPointLightsUniformBuffer()
	: GlUniformBuffer("ubo_pointLights")
{
}

void GlPointLightsUniformBuffer::SetPointLight(const PointLight& pointLight)
{
	m_PointLight = &pointLight;
}

void GlPointLightsUniformBuffer::Update(const Camera& camera, const GlGraphicsEngine& graphicsEngine)
{
	// TODO: Support multiple point lights.
	if (graphicsEngine.m_PointLights.size() != 0)
	{
		SetPointLight(*graphicsEngine.m_PointLights[0]);
	}
}

void GlPointLightsUniformBuffer::Send()
{
	if (!m_PointLight)
		return;

	unsigned int offset = 0;
	m_PointLightData.SendToDevice(*m_PointLight, offset);
}

unsigned int GlPointLightsUniformBuffer::GetUniformBufferSize() const
{
	unsigned int totalSize = 0;
	m_PointLightData.AddAlignedSizeToTotalSize(totalSize);

	return totalSize;
}
