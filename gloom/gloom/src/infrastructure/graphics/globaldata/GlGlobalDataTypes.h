#pragma once

#include <glm/glm.hpp>

#include "GlGlobalDataType.h"

class DirectionalLight;
class PointLight;

class GlGlobalDataMat4 : public GlGlobalDataType<glm::mat4>
{
public:
	GlGlobalDataMat4();

	void SendToDevice(const glm::mat4& value, unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;
};

class GlGlobalDataVec3 : public GlGlobalDataType<glm::vec3>
{
public:
	GlGlobalDataVec3();

	void SendToDevice(const glm::vec3& value, unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;
};

class GlGlobalDataFloat : public GlGlobalDataType<float>
{
public:
	GlGlobalDataFloat();

	void SendToDevice(const float& value, unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;
};

class GlGlobalDataDirectionalLight : public GlGlobalDataType<DirectionalLight>
{
public:
	GlGlobalDataDirectionalLight();

	void SendToDevice(const DirectionalLight& value, unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;

private:
	GlGlobalDataVec3 m_DirectionGlobalData;
	GlGlobalDataVec3 m_AmbientColorGlobalData;
	GlGlobalDataVec3 m_DiffuseColorGlobalData;
	GlGlobalDataVec3 m_SpecularColorGlobalData;
};

class GlGlobalDataPointLight : public GlGlobalDataType<PointLight>
{
public:
	GlGlobalDataPointLight();
	
	void SendToDevice(const PointLight& value, unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;

private:
	GlGlobalDataVec3 m_PositionGlobalData;
	GlGlobalDataVec3 m_AmbientColorGlobalData;
	GlGlobalDataVec3 m_DiffuseColorGlobalData;
	GlGlobalDataVec3 m_SpecularColorGlobalData;
	GlGlobalDataFloat m_AttenuationConstantGlobalData;
	GlGlobalDataFloat m_AttenuationLinearGlobalData;
	GlGlobalDataFloat m_AttenuationQuadraticGlobalData;
};
