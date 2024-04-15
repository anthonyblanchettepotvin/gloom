#pragma once

#include <glm/glm.hpp>

#include "GlGlobalData.h"
#include "GlGlobalDataTypes.h"

class GlMatricesUniformBuffer : public GlGlobalData
{
public:
	GlMatricesUniformBuffer();

	void SetViewTransform(const glm::mat4& viewTransform);
	void SetSkyboxTransform(const glm::mat4& skyboxTransform);
	void SetProjectionTransform(const glm::mat4& projectionTransform);

protected:
	void Send() override;

	unsigned int GetUniformBufferSize() const override;

private:
	glm::mat4 m_ViewTransform{ glm::mat4() };
	glm::mat4 m_SkyboxTransform{ glm::mat4() };
	glm::mat4 m_ProjectionTransform{ glm::mat4() };

	GlGlobalDataMat4 m_ViewTransformData;
	GlGlobalDataMat4 m_SkyboxTransformData;
	GlGlobalDataMat4 m_ProjectionTransformData;
};
