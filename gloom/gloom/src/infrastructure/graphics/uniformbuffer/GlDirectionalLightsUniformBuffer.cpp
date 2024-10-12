#include "GlDirectionalLightsUniformBuffer.h"

#include "../../../engine/graphics/lighting/DirectionalLight.h"

#include "../engine/GlGraphicsEngine.h"

GlDirectionalLightsUniformBuffer::GlDirectionalLightsUniformBuffer()
	: GlUniformBuffer("ubo_directionalLights")
{
}

void GlDirectionalLightsUniformBuffer::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	m_DirectionalLight = &directionalLight;
}

void GlDirectionalLightsUniformBuffer::Update(const Camera& camera, const GlGraphicsEngine& graphicsEngine)
{
	// TODO: Support multiple directional lights.
	if (graphicsEngine.m_DirectionalLights.size() != 0)
	{
		SetDirectionalLight(*graphicsEngine.m_DirectionalLights[0]);
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
