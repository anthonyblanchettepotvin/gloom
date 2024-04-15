#include "GlGlobalDataTypes.h"

#include <glad/glad.h>

#include "../../../engine/graphics/lighting/DirectionalLight.h"
#include "../../../engine/graphics/lighting/PointLight.h"
#include "../../../engine/math/Math.hpp"

GlGlobalDataMat4::GlGlobalDataMat4()
{
}

void GlGlobalDataMat4::SendToDevice(const glm::mat4& value, unsigned int& offset)
{
	offset = Math::Align(offset, GetBaseAlignment());

	// TODO: Might need to store the value since in takes a pointer.
	glBufferSubData(GL_UNIFORM_BUFFER, offset, GetSize(), &value);

	offset += GetSize();
}

unsigned int GlGlobalDataMat4::GetBaseAlignment() const
{
	return 16;
}

unsigned int GlGlobalDataMat4::GetSize() const
{
	return sizeof(glm::mat4);
}

GlGlobalDataVec3::GlGlobalDataVec3()
{
}

void GlGlobalDataVec3::SendToDevice(const glm::vec3& value, unsigned int& offset)
{
	offset = Math::Align(offset, GetBaseAlignment());

	// TODO: Might need to store the value since in takes a pointer.
	glBufferSubData(GL_UNIFORM_BUFFER, offset, GetSize(), &value);

	offset += GetSize();
}

unsigned int GlGlobalDataVec3::GetBaseAlignment() const
{
	return 16;
}

unsigned int GlGlobalDataVec3::GetSize() const
{
	return sizeof(glm::vec3);
}

GlGlobalDataFloat::GlGlobalDataFloat()
{
}

void GlGlobalDataFloat::SendToDevice(const float& value, unsigned int& offset)
{
	offset = Math::Align(offset, GetBaseAlignment());

	// TODO: Might need to store the value since in takes a pointer.
	glBufferSubData(GL_UNIFORM_BUFFER, offset, GetSize(), &value);

	offset += GetSize();
}

unsigned int GlGlobalDataFloat::GetBaseAlignment() const
{
	return 4;
}

unsigned int GlGlobalDataFloat::GetSize() const
{
	return sizeof(float);
}

GlGlobalDataDirectionalLight::GlGlobalDataDirectionalLight()
{
}

void GlGlobalDataDirectionalLight::SendToDevice(const DirectionalLight& value, unsigned int& offset)
{
	m_DirectionGlobalData.SendToDevice(value.GetDirection(), offset);
	m_AmbientColorGlobalData.SendToDevice(value.GetAmbientColor(), offset);
	m_DiffuseColorGlobalData.SendToDevice(value.GetDiffuseColor(), offset);
	m_SpecularColorGlobalData.SendToDevice(value.GetSpecularColor(), offset);
}

unsigned int GlGlobalDataDirectionalLight::GetBaseAlignment() const
{
	return 16;
}

unsigned int GlGlobalDataDirectionalLight::GetSize() const
{
	unsigned int size = 0;
	m_DirectionGlobalData.AddAlignedSizeToTotalSize(size);
	m_AmbientColorGlobalData.AddAlignedSizeToTotalSize(size);
	m_DiffuseColorGlobalData.AddAlignedSizeToTotalSize(size);
	m_SpecularColorGlobalData.AddAlignedSizeToTotalSize(size);

	return size;
}

GlGlobalDataPointLight::GlGlobalDataPointLight()
{
}

void GlGlobalDataPointLight::SendToDevice(const PointLight& value, unsigned int& offset)
{
	m_PositionGlobalData.SendToDevice(value.GetPosition(), offset);
	m_AmbientColorGlobalData.SendToDevice(value.GetAmbientColor(), offset);
	m_DiffuseColorGlobalData.SendToDevice(value.GetDiffuseColor(), offset);
	m_SpecularColorGlobalData.SendToDevice(value.GetSpecularColor(), offset);
	m_AttenuationConstantGlobalData.SendToDevice(value.GetAttenuation().Constant, offset);
	m_AttenuationLinearGlobalData.SendToDevice(value.GetAttenuation().Linear, offset);
	m_AttenuationQuadraticGlobalData.SendToDevice(value.GetAttenuation().Quadratic, offset);
}

unsigned int GlGlobalDataPointLight::GetBaseAlignment() const
{
	return 16;
}

unsigned int GlGlobalDataPointLight::GetSize() const
{
	unsigned int size = 0;
	m_PositionGlobalData.AddAlignedSizeToTotalSize(size);
	m_AmbientColorGlobalData.AddAlignedSizeToTotalSize(size);
	m_DiffuseColorGlobalData.AddAlignedSizeToTotalSize(size);
	m_SpecularColorGlobalData.AddAlignedSizeToTotalSize(size);
	m_AttenuationConstantGlobalData.AddAlignedSizeToTotalSize(size);
	m_AttenuationLinearGlobalData.AddAlignedSizeToTotalSize(size);
	m_AttenuationQuadraticGlobalData.AddAlignedSizeToTotalSize(size);

	return size;
}
