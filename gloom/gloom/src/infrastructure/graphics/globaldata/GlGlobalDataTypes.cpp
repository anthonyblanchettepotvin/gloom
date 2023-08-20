#include "GlGlobalDataTypes.h"

#include <glad/glad.h>

GlGlobalDataMat4::GlGlobalDataMat4(glm::mat4& value)
	: m_Value(value)
{
}

unsigned int GlGlobalDataMat4::GetBaseAlignment()
{
	return 16;
}

unsigned int GlGlobalDataMat4::GetSize()
{
	return sizeof(glm::mat4);
}

void GlGlobalDataMat4::SendToDevice(unsigned int& offset)
{
	offset = GetBaseAlignment() == 0 ? GetBaseAlignment() : ceil((double) offset / GetBaseAlignment()) * GetBaseAlignment();

	glBufferSubData(GL_UNIFORM_BUFFER, offset, GetSize(), &m_Value);

	offset += GetSize();
}

GlGlobalDataVec3::GlGlobalDataVec3(glm::vec3& value)
	: m_Value(value)
{
}

unsigned int GlGlobalDataVec3::GetBaseAlignment()
{
	return 16;
}

unsigned int GlGlobalDataVec3::GetSize()
{
	return sizeof(glm::vec3);
}

void GlGlobalDataVec3::SendToDevice(unsigned int& offset)
{
	offset = GetBaseAlignment() == 0 ? GetBaseAlignment() : ceil((double) offset / GetBaseAlignment()) * GetBaseAlignment();

	glBufferSubData(GL_UNIFORM_BUFFER, offset, GetSize(), &m_Value);

	offset += GetSize();
}

GlGlobalDataFloat::GlGlobalDataFloat(float& value)
	: m_Value(value)
{
}

unsigned int GlGlobalDataFloat::GetBaseAlignment()
{
	return 4;
}

unsigned int GlGlobalDataFloat::GetSize()
{
	return sizeof(float);
}

void GlGlobalDataFloat::SendToDevice(unsigned int& offset)
{
	offset = GetBaseAlignment() == 0 ? GetBaseAlignment() : ceil((double) offset / GetBaseAlignment()) * GetBaseAlignment();

	glBufferSubData(GL_UNIFORM_BUFFER, offset, GetSize(), &m_Value);

	offset += GetSize();
}

GlGlobalDataDirectionalLight::GlGlobalDataDirectionalLight(DirectionalLight& value)
	: m_Value(value)
	, m_DirectionGlobalData(value.GetDirectionReference())
	, m_AmbientColorGlobalData(value.GetAmbientColorReference())
	, m_DiffuseColorGlobalData(value.GetDiffuseColorReference())
	, m_SpecularColorGlobalData(value.GetSpecularColorReference())
{
}

unsigned int GlGlobalDataDirectionalLight::GetBaseAlignment()
{
	return 16;
}

unsigned int GlGlobalDataDirectionalLight::GetSize()
{
	return m_DirectionGlobalData.GetSize()
		+ m_AmbientColorGlobalData.GetSize()
		+ m_DiffuseColorGlobalData.GetSize()
		+ m_SpecularColorGlobalData.GetSize() + 12; // FIXME: Avoid hard-coding the total alignment value
}

void GlGlobalDataDirectionalLight::SendToDevice(unsigned int& offset)
{
	m_DirectionGlobalData.SendToDevice(offset);
	m_AmbientColorGlobalData.SendToDevice(offset);
	m_DiffuseColorGlobalData.SendToDevice(offset);
	m_SpecularColorGlobalData.SendToDevice(offset);
}


GlGlobalDataPointLight::GlGlobalDataPointLight(PointLight& value)
	: m_Value(value)
	, m_PositionGlobalData(value.GetPositionReference())
	, m_AmbientColorGlobalData(value.GetAmbientColorReference())
	, m_DiffuseColorGlobalData(value.GetDiffuseColorReference())
	, m_SpecularColorGlobalData(value.GetSpecularColorReference())
	, m_AttenuationConstantGlobalData(value.GetAttenuationReference().constant)
	, m_AttenuationLinearGlobalData(value.GetAttenuationReference().linear)
	, m_AttenuationQuadraticGlobalData(value.GetAttenuationReference().quadratic)
{
}

unsigned int GlGlobalDataPointLight::GetBaseAlignment()
{
	return 16;
}

unsigned int GlGlobalDataPointLight::GetSize()
{
	return m_PositionGlobalData.GetSize()
		+ m_AmbientColorGlobalData.GetSize()
		+ m_DiffuseColorGlobalData.GetSize()
		+ m_SpecularColorGlobalData.GetSize()
		+ m_AttenuationConstantGlobalData.GetSize()
		+ m_AttenuationLinearGlobalData.GetSize()
		+ m_AttenuationQuadraticGlobalData.GetSize() + 12; // FIXME: Avoid hard-coding the total alignment value
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
