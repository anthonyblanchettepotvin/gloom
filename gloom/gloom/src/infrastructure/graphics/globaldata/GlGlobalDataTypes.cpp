#include "GlGlobalDataTypes.h"

#include <glad/glad.h>

#include "../../../engine/graphics/lighting/DirectionalLight.h"
#include "../../../engine/graphics/lighting/PointLight.h"

GlGlobalDataMat4::GlGlobalDataMat4(glm::mat4& value)
	: m_Value(value)
{
}

void GlGlobalDataMat4::SendToDevice(unsigned int& offset)
{
	offset = GetBaseAlignment() == 0 ? GetBaseAlignment() : ceil((double)offset / GetBaseAlignment()) * GetBaseAlignment();

	glBufferSubData(GL_UNIFORM_BUFFER, offset, GetSize(), &m_Value);

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

GlGlobalDataVec3::GlGlobalDataVec3(glm::vec3& value)
	: m_Value(value)
{
}

void GlGlobalDataVec3::SendToDevice(unsigned int& offset)
{
	offset = GetBaseAlignment() == 0 ? GetBaseAlignment() : ceil((double)offset / GetBaseAlignment()) * GetBaseAlignment();

	glBufferSubData(GL_UNIFORM_BUFFER, offset, GetSize(), &m_Value);

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

GlGlobalDataFloat::GlGlobalDataFloat(float& value)
	: m_Value(value)
{
}

void GlGlobalDataFloat::SendToDevice(unsigned int& offset)
{
	offset = GetBaseAlignment() == 0 ? GetBaseAlignment() : ceil((double)offset / GetBaseAlignment()) * GetBaseAlignment();

	glBufferSubData(GL_UNIFORM_BUFFER, offset, GetSize(), &m_Value);

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

GlGlobalDataDirectionalLight::GlGlobalDataDirectionalLight(DirectionalLight& value)
	: m_Value(value)
	, m_DirectionGlobalData(value.GetDirection())
	, m_AmbientColorGlobalData(value.GetAmbientColor())
	, m_DiffuseColorGlobalData(value.GetDiffuseColor())
	, m_SpecularColorGlobalData(value.GetSpecularColor())
{
}

void GlGlobalDataDirectionalLight::SendToDevice(unsigned int& offset)
{
	m_DirectionGlobalData.SendToDevice(offset);
	m_AmbientColorGlobalData.SendToDevice(offset);
	m_DiffuseColorGlobalData.SendToDevice(offset);
	m_SpecularColorGlobalData.SendToDevice(offset);
}

unsigned int GlGlobalDataDirectionalLight::GetBaseAlignment() const
{
	return 16;
}

unsigned int GlGlobalDataDirectionalLight::GetSize() const
{
	return m_DirectionGlobalData.GetSize()
		+ m_AmbientColorGlobalData.GetSize()
		+ m_DiffuseColorGlobalData.GetSize()
		+ m_SpecularColorGlobalData.GetSize() + 12; // FIXME: Avoid hard-coding the total alignment value
}

GlGlobalDataPointLight::GlGlobalDataPointLight(PointLight& value)
	: m_Value(value)
	, m_PositionGlobalData(value.GetPosition())
	, m_AmbientColorGlobalData(value.GetAmbientColor())
	, m_DiffuseColorGlobalData(value.GetDiffuseColor())
	, m_SpecularColorGlobalData(value.GetSpecularColor())
	, m_AttenuationConstantGlobalData(value.GetAttenuation().Constant)
	, m_AttenuationLinearGlobalData(value.GetAttenuation().Linear)
	, m_AttenuationQuadraticGlobalData(value.GetAttenuation().Quadratic)
{
}

void GlGlobalDataPointLight::SendToDevice(unsigned int& offset)
{
	m_PositionGlobalData.SendToDevice(offset);
	m_AmbientColorGlobalData.SendToDevice(offset);
	m_DiffuseColorGlobalData.SendToDevice(offset);
	m_SpecularColorGlobalData.SendToDevice(offset);
	m_AttenuationConstantGlobalData.SendToDevice(offset);
	m_AttenuationLinearGlobalData.SendToDevice(offset);
	m_AttenuationQuadraticGlobalData.SendToDevice(offset);
}

unsigned int GlGlobalDataPointLight::GetBaseAlignment() const
{
	return 16;
}

unsigned int GlGlobalDataPointLight::GetSize() const
{
	return m_PositionGlobalData.GetSize()
		+ m_AmbientColorGlobalData.GetSize()
		+ m_DiffuseColorGlobalData.GetSize()
		+ m_SpecularColorGlobalData.GetSize()
		+ m_AttenuationConstantGlobalData.GetSize()
		+ m_AttenuationLinearGlobalData.GetSize()
		+ m_AttenuationQuadraticGlobalData.GetSize() + 12; // FIXME: Avoid hard-coding the total alignment value
}
