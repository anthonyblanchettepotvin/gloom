#pragma once

#include <glm/glm.hpp>

#include "GlUniformBuffer.h"
#include "GlUniformBufferDataTypes.h"

class GlMatricesUniformBuffer : public GlUniformBuffer
{
public:
	GlMatricesUniformBuffer();

	void SetViewTransform(const glm::mat4& viewTransform);
	void SetSkyboxTransform(const glm::mat4& skyboxTransform);
	void SetProjectionTransform(const glm::mat4& projectionTransform);

	void Update(const Camera& camera, const GlGraphicsData& graphicsData) override;

protected:
	void Send() override;

	unsigned int GetUniformBufferSize() const override;

private:
	glm::mat4 m_ViewTransform{ glm::mat4() };
	glm::mat4 m_SkyboxTransform{ glm::mat4() };
	glm::mat4 m_ProjectionTransform{ glm::mat4() };

	GlUniformBufferDataMat4 m_ViewTransformData;
	GlUniformBufferDataMat4 m_SkyboxTransformData;
	GlUniformBufferDataMat4 m_ProjectionTransformData;
};
