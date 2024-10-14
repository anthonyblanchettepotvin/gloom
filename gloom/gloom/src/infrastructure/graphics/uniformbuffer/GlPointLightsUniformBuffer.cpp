#include "GlPointLightsUniformBuffer.h"

#include "../../../engine/graphics/lighting/PointLight.h"

#include "../engine/GlGraphicsData.h"

GlPointLightsUniformBuffer::GlPointLightsUniformBuffer()
	: GlUniformBuffer("ubo_pointLights")
{
}

void GlPointLightsUniformBuffer::SetPointLight(const PointLight& pointLight)
{
	m_PointLight = &pointLight;
}

void GlPointLightsUniformBuffer::Update(const Camera& camera, const GlGraphicsData& graphicsData)
{
	// TODO: Support multiple point lights.
	if (graphicsData.GetPointLights().size() != 0)
	{
		SetPointLight(*graphicsData.GetPointLights()[0]);
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
