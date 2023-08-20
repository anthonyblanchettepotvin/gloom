#pragma once

#include <glm/glm.hpp>

#include "../../../engine/graphics/lighting/DirectionalLight.h"
#include "../../../engine/graphics/lighting/PointLight.h"

#include "GlGlobalDataType.h"

class GlGlobalDataMat4 : public GlGlobalDataType
{
public:
	GlGlobalDataMat4(glm::mat4& value);

	unsigned int GetBaseAlignment() override;
	unsigned int GetSize() override;

	void SendToDevice(unsigned int& offset) override;

private:
	glm::mat4& m_Value;
};

class GlGlobalDataVec3 : public GlGlobalDataType
{
public:
	GlGlobalDataVec3(glm::vec3& value);

	unsigned int GetBaseAlignment() override;
	unsigned int GetSize() override;

	void SendToDevice(unsigned int& offset) override;

private:
	glm::vec3& m_Value;
};

class GlGlobalDataFloat : public GlGlobalDataType
{
public:
	GlGlobalDataFloat(float& value);

	unsigned int GetBaseAlignment() override;
	unsigned int GetSize() override;

	void SendToDevice(unsigned int& offset) override;

private:
	float& m_Value;
};

class GlGlobalDataDirectionalLight : public GlGlobalDataType
{
public:
	GlGlobalDataDirectionalLight(DirectionalLight& value);

	unsigned int GetBaseAlignment() override;
	unsigned int GetSize() override;

	void SendToDevice(unsigned int& offset) override;

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

	unsigned int GetBaseAlignment() override;
	unsigned int GetSize() override;

	void SendToDevice(unsigned int& offset) override;

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
