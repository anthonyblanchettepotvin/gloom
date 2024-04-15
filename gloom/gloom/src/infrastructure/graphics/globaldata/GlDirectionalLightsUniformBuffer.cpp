#include "GlDirectionalLightsUniformBuffer.h"

#include "GlGlobalDataTypes.h"

#include "../../../engine/graphics/lighting/DirectionalLight.h"

GlDirectionalLightsUniformBuffer::GlDirectionalLightsUniformBuffer()
	: GlGlobalData("ubo_directionalLights")
{
}

void GlDirectionalLightsUniformBuffer::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	m_DirectionalLight = &directionalLight;
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
