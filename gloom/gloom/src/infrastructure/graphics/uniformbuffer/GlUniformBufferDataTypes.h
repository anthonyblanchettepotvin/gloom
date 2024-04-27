#pragma once

#include <glm/glm.hpp>

#include "GlUniformBufferDataType.h"

class DirectionalLight;
class PointLight;

class GlUniformBufferDataMat4 : public GlUniformBufferDataType<glm::mat4>
{
public:
	GlUniformBufferDataMat4();

	void SendToDevice(const glm::mat4& value, unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;
};

class GlUniformBufferDataVec3 : public GlUniformBufferDataType<glm::vec3>
{
public:
	GlUniformBufferDataVec3();

	void SendToDevice(const glm::vec3& value, unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;
};

class GlUniformBufferDataFloat : public GlUniformBufferDataType<float>
{
public:
	GlUniformBufferDataFloat();

	void SendToDevice(const float& value, unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;
};

class GlUniformBufferDataDirectionalLight : public GlUniformBufferDataType<DirectionalLight>
{
public:
	GlUniformBufferDataDirectionalLight();

	void SendToDevice(const DirectionalLight& value, unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;

private:
	GlUniformBufferDataVec3 m_DirectionUniformBufferData;
	GlUniformBufferDataVec3 m_AmbientColorUniformBufferData;
	GlUniformBufferDataVec3 m_DiffuseColorUniformBufferData;
	GlUniformBufferDataVec3 m_SpecularColorUniformBufferData;
};

class GlUniformBufferDataPointLight : public GlUniformBufferDataType<PointLight>
{
public:
	GlUniformBufferDataPointLight();
	
	void SendToDevice(const PointLight& value, unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;

private:
	GlUniformBufferDataVec3 m_PositionUniformBufferData;
	GlUniformBufferDataVec3 m_AmbientColorUniformBufferData;
	GlUniformBufferDataVec3 m_DiffuseColorUniformBufferData;
	GlUniformBufferDataVec3 m_SpecularColorUniformBufferData;
	GlUniformBufferDataFloat m_AttenuationConstantUniformBufferData;
	GlUniformBufferDataFloat m_AttenuationLinearUniformBufferData;
	GlUniformBufferDataFloat m_AttenuationQuadraticUniformBufferData;
};
