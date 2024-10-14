#pragma once

#include <glm/glm.hpp>

#include "GlUniformBuffer.h"
#include "GlUniformBufferDataTypes.h"

class GlCameraUniformBuffer : public GlUniformBuffer
{
public:
	GlCameraUniformBuffer();

	void SetCameraPosition(const glm::vec3& cameraPosition);

	void Update(const Camera& camera, const GlGraphicsData& graphicsData) override;

protected:
	void Send() override;

	unsigned int GetUniformBufferSize() const override;

private:
	glm::vec3 m_CameraPosition{ glm::vec3() };

	GlUniformBufferDataVec3 m_CameraPositionData;
};
