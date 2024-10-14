#include "GlUniformBufferDataTypes.h"

#include <glad/glad.h>

#include "../../../engine/graphics/lighting/DirectionalLight.h"
#include "../../../engine/graphics/lighting/PointLight.h"
#include "../../../engine/math/Math.hpp"

GlUniformBufferDataMat4::GlUniformBufferDataMat4()
{
}

void GlUniformBufferDataMat4::SendToDevice(const glm::mat4& value, unsigned int& offset)
{
	offset = Math::Align(offset, GetBaseAlignment());

	glBufferSubData(GL_UNIFORM_BUFFER, offset, GetSize(), &value);

	offset += GetSize();
}

unsigned int GlUniformBufferDataMat4::GetBaseAlignment() const
{
	return 16;
}

unsigned int GlUniformBufferDataMat4::GetSize() const
{
	return sizeof(glm::mat4);
}

GlUniformBufferDataVec3::GlUniformBufferDataVec3()
{
}

void GlUniformBufferDataVec3::SendToDevice(const glm::vec3& value, unsigned int& offset)
{
	offset = Math::Align(offset, GetBaseAlignment());

	glBufferSubData(GL_UNIFORM_BUFFER, offset, GetSize(), &value);

	offset += GetSize();
}

unsigned int GlUniformBufferDataVec3::GetBaseAlignment() const
{
	return 16;
}

unsigned int GlUniformBufferDataVec3::GetSize() const
{
	return sizeof(glm::vec3);
}

GlUniformBufferDataFloat::GlUniformBufferDataFloat()
{
}

void GlUniformBufferDataFloat::SendToDevice(const float& value, unsigned int& offset)
{
	offset = Math::Align(offset, GetBaseAlignment());

	glBufferSubData(GL_UNIFORM_BUFFER, offset, GetSize(), &value);

	offset += GetSize();
}

unsigned int GlUniformBufferDataFloat::GetBaseAlignment() const
{
	return 4;
}

unsigned int GlUniformBufferDataFloat::GetSize() const
{
	return sizeof(float);
}

GlUniformBufferDataDirectionalLight::GlUniformBufferDataDirectionalLight()
{
}

void GlUniformBufferDataDirectionalLight::SendToDevice(const DirectionalLight& value, unsigned int& offset)
{
	m_DirectionUniformBufferData.SendToDevice(value.GetDirection(), offset);
	m_AmbientColorUniformBufferData.SendToDevice(value.GetAmbientColor(), offset);
	m_DiffuseColorUniformBufferData.SendToDevice(value.GetDiffuseColor(), offset);
	m_SpecularColorUniformBufferData.SendToDevice(value.GetSpecularColor(), offset);
}

unsigned int GlUniformBufferDataDirectionalLight::GetBaseAlignment() const
{
	return 16;
}

unsigned int GlUniformBufferDataDirectionalLight::GetSize() const
{
	unsigned int size = 0;
	m_DirectionUniformBufferData.AddAlignedSizeToTotalSize(size);
	m_AmbientColorUniformBufferData.AddAlignedSizeToTotalSize(size);
	m_DiffuseColorUniformBufferData.AddAlignedSizeToTotalSize(size);
	m_SpecularColorUniformBufferData.AddAlignedSizeToTotalSize(size);

	return size;
}

GlUniformBufferDataPointLight::GlUniformBufferDataPointLight()
{
}

void GlUniformBufferDataPointLight::SendToDevice(const PointLight& value, unsigned int& offset)
{
	m_PositionUniformBufferData.SendToDevice(value.GetPosition(), offset);
	m_AmbientColorUniformBufferData.SendToDevice(value.GetAmbientColor(), offset);
	m_DiffuseColorUniformBufferData.SendToDevice(value.GetDiffuseColor(), offset);
	m_SpecularColorUniformBufferData.SendToDevice(value.GetSpecularColor(), offset);
	m_AttenuationConstantUniformBufferData.SendToDevice(value.GetAttenuation().Constant, offset);
	m_AttenuationLinearUniformBufferData.SendToDevice(value.GetAttenuation().Linear, offset);
	m_AttenuationQuadraticUniformBufferData.SendToDevice(value.GetAttenuation().Quadratic, offset);
}

unsigned int GlUniformBufferDataPointLight::GetBaseAlignment() const
{
	return 16;
}

unsigned int GlUniformBufferDataPointLight::GetSize() const
{
	unsigned int size = 0;
	m_PositionUniformBufferData.AddAlignedSizeToTotalSize(size);
	m_AmbientColorUniformBufferData.AddAlignedSizeToTotalSize(size);
	m_DiffuseColorUniformBufferData.AddAlignedSizeToTotalSize(size);
	m_SpecularColorUniformBufferData.AddAlignedSizeToTotalSize(size);
	m_AttenuationConstantUniformBufferData.AddAlignedSizeToTotalSize(size);
	m_AttenuationLinearUniformBufferData.AddAlignedSizeToTotalSize(size);
	m_AttenuationQuadraticUniformBufferData.AddAlignedSizeToTotalSize(size);

	return size;
}
