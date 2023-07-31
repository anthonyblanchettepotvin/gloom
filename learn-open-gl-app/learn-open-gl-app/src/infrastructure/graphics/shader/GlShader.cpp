#include "GlShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "../globaldata/GlGlobalData.h"

GlShader::GlShader(unsigned int id)
	: m_Id(id), m_SamplerIndex(0)
{
}

void GlShader::Use()
{
	glUseProgram(m_Id);

	m_SamplerIndex = 0;
}

void GlShader::SetBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(m_Id, name.c_str()), (int)value);
}

void GlShader::SetInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(m_Id, name.c_str()), value);
}

void GlShader::SetFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(m_Id, name.c_str()), value);
}

void GlShader::SetFloatVec3(const std::string& name, glm::vec3 value)
{
	glUniform3fv(glGetUniformLocation(m_Id, name.c_str()), 1, glm::value_ptr(value));
}

void GlShader::SetFloatMat3(const std::string& name, glm::mat3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void GlShader::SetFloatMat4(const std::string& name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void GlShader::SetTexture(const std::string& name, Texture* texture)
{
	if (GlTexture* glTexture = dynamic_cast<GlTexture*>(texture))
	{
		glTexture->Use(m_SamplerIndex);

		SetInt(name, m_SamplerIndex);

		m_SamplerIndex++;
	}
}

void GlShader::SetCubemap(const std::string& name, Cubemap* cubemap)
{
	if (GlCubemap* glCubemap = dynamic_cast<GlCubemap*>(cubemap))
	{
		glCubemap->Use(m_SamplerIndex);

		SetInt(name, m_SamplerIndex);

		m_SamplerIndex++;
	}
}

void GlShader::BindToGlobalData(GlobalData* globalData)
{
	if (GlGlobalData* glGlobalData = dynamic_cast<GlGlobalData*>(globalData))
	{
		glUniformBlockBinding(m_Id, glGetUniformBlockIndex(m_Id, glGlobalData->GetName().c_str()), glGlobalData->GetIndex());
	}
}
