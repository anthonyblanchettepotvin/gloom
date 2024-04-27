#include "GlCameraUniformBuffer.h"

GlCameraUniformBuffer::GlCameraUniformBuffer()
	: GlUniformBuffer("ubo_camera")
{
}

void GlCameraUniformBuffer::SetCameraPosition(const glm::vec3& cameraPosition)
{
	m_CameraPosition = cameraPosition;
}

void GlCameraUniformBuffer::Send()
{
	unsigned int offset = 0;
	m_CameraPositionData.SendToDevice(m_CameraPosition, offset);
}

unsigned int GlCameraUniformBuffer::GetUniformBufferSize() const
{
	unsigned int totalSize = 0;
	m_CameraPositionData.AddAlignedSizeToTotalSize(totalSize);

	return totalSize;
}
