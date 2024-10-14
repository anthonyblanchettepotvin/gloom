#include "GlDirectionalLightsUniformBuffer.h"

#include "../../../engine/graphics/lighting/DirectionalLight.h"

#include "../engine/GlGraphicsData.h"

GlDirectionalLightsUniformBuffer::GlDirectionalLightsUniformBuffer()
	: GlUniformBuffer("ubo_directionalLights")
{
}

void GlDirectionalLightsUniformBuffer::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	m_DirectionalLight = &directionalLight;
}

void GlDirectionalLightsUniformBuffer::Update(const Camera& camera, const GlGraphicsData& graphicsData)
{
	// TODO: Support multiple directional lights.
	if (graphicsData.GetDirectionalLights().size() != 0)
	{
		SetDirectionalLight(*graphicsData.GetDirectionalLights()[0]);
	}
}

void GlDirectionalLightsUniformBuffer::Send()
{
	if (!m_DirectionalLight)
		return;

	unsigned int offset = 0;
	m_DirectionalLightData.SendToDevice(*m_DirectionalLight, offset);
}

unsigned int GlDirectionalLightsUniformBuffer::GetUniformBufferSize() const
{
	unsigned int totalSize = 0;
	m_DirectionalLightData.AddAlignedSizeToTotalSize(totalSize);

	return totalSize;
}
