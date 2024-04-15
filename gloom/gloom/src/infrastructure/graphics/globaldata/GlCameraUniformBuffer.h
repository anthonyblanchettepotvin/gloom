#pragma once

#include <glm/glm.hpp>

#include "GlGlobalData.h"
#include "GlGlobalDataTypes.h"

class GlCameraUniformBuffer : public GlGlobalData
{
public:
	GlCameraUniformBuffer();

	void SetCameraPosition(const glm::vec3& cameraPosition);

protected:
	void Send() override;

	unsigned int GetUniformBufferSize() const override;

private:
	glm::vec3 m_CameraPosition{ glm::vec3() };

	GlGlobalDataVec3 m_CameraPositionData;
};
