#include "GlMatricesUniformBuffer.h"

#include "../../../engine/graphics/camera/Camera.h"

GlMatricesUniformBuffer::GlMatricesUniformBuffer()
	: GlUniformBuffer("ubo_matrices")
{
}

void GlMatricesUniformBuffer::SetViewTransform(const glm::mat4& viewTransform)
{
	m_ViewTransform = viewTransform;
}

void GlMatricesUniformBuffer::SetSkyboxTransform(const glm::mat4& skyboxTransform)
{
	m_SkyboxTransform = skyboxTransform;
}

void GlMatricesUniformBuffer::SetProjectionTransform(const glm::mat4& projectionTransform)
{
	m_ProjectionTransform = projectionTransform;
}

void GlMatricesUniformBuffer::Update(const Camera& camera, const GlGraphicsData& graphicsData)
{
	SetViewTransform(camera.GetViewMatrix());
	SetSkyboxTransform(camera.GetSkyboxMatrix());
	SetProjectionTransform(camera.GetProjectionMatrix());
}

void GlMatricesUniformBuffer::Send()
{
	unsigned int offset = 0;
	m_ViewTransformData.SendToDevice(m_ViewTransform, offset);
	m_SkyboxTransformData.SendToDevice(m_SkyboxTransform, offset);
	m_ProjectionTransformData.SendToDevice(m_ProjectionTransform, offset);
}

unsigned int GlMatricesUniformBuffer::GetUniformBufferSize() const
{
	unsigned int totalSize = 0;
	m_ViewTransformData.AddAlignedSizeToTotalSize(totalSize);
	m_SkyboxTransformData.AddAlignedSizeToTotalSize(totalSize);
	m_ProjectionTransformData.AddAlignedSizeToTotalSize(totalSize);

	return totalSize;
}
