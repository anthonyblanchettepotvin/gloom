#pragma once

#include <glm/glm.hpp>

#include "GlGlobalDataType.h"

class DirectionalLight;
class PointLight;

class GlGlobalDataMat4 : public GlGlobalDataType
{
public:
	GlGlobalDataMat4(glm::mat4& value);

	void SendToDevice(unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;

private:
	glm::mat4& m_Value;
};

class GlGlobalDataVec3 : public GlGlobalDataType
{
public:
	GlGlobalDataVec3(glm::vec3& value);

	void SendToDevice(unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;

private:
	glm::vec3& m_Value;
};

class GlGlobalDataFloat : public GlGlobalDataType
{
public:
	GlGlobalDataFloat(float& value);

	void SendToDevice(unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;

private:
	float& m_Value;
};

class GlGlobalDataDirectionalLight : public GlGlobalDataType
{
public:
	GlGlobalDataDirectionalLight(DirectionalLight& value);

	void SendToDevice(unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;

private:
	DirectionalLight& m_Value;

	GlGlobalDataVec3 m_DirectionGlobalData;
	GlGlobalDataVec3 m_AmbientColorGlobalData;
	GlGlobalDataVec3 m_DiffuseColorGlobalData;
	GlGlobalDataVec3 m_SpecularColorGlobalData;
};

class GlGlobalDataPointLight : public GlGlobalDataType
{
public:
	GlGlobalDataPointLight(PointLight& value);

	void SendToDevice(unsigned int& offset) override;

	unsigned int GetBaseAlignment() const override;
	unsigned int GetSize() const override;

private:
	PointLight& m_Value;

	GlGlobalDataVec3 m_PositionGlobalData;
	GlGlobalDataVec3 m_AmbientColorGlobalData;
	GlGlobalDataVec3 m_DiffuseColorGlobalData;
	GlGlobalDataVec3 m_SpecularColorGlobalData;
	GlGlobalDataFloat m_AttenuationConstantGlobalData;
	GlGlobalDataFloat m_AttenuationLinearGlobalData;
	GlGlobalDataFloat m_AttenuationQuadraticGlobalData;
};
