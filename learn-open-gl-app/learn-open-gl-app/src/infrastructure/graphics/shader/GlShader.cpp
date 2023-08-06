#include "GlShader.h"

#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "../../../engine/graphics/material/MaterialAttributes.h"

#include "../globaldata/GlGlobalData.h"

GlShader::GlShader(unsigned int id)
	: m_Id(id), m_SamplerIndex(0)
{
}

void GlShader::InitializeMaterialTemplate()
{
	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = GL_ACTIVE_UNIFORM_MAX_LENGTH; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length

	GLint nbUniforms;
	glGetProgramiv(m_Id, GL_ACTIVE_UNIFORMS, &nbUniforms);

	for (size_t i = 0; i < nbUniforms; i++)
	{
		glGetActiveUniform(m_Id, (GLint)i, bufSize, &length, &size, &type, name);

		std::string cppName = (std::string)name;

		std::string structName = cppName.substr(0, cppName.find_first_of('.'));

		if (structName != "material")
			continue;

		switch (type)
		{
		case GL_SAMPLER_2D:
		{
			std::unique_ptr<MaterialAttribute> attribute = std::make_unique<TextureMaterialAttribute>(cppName);
			m_MaterialTemplate.AddAttribute(attribute);
			break;
		}
		case GL_FLOAT:
		{
			std::unique_ptr<MaterialAttribute> attribute = std::make_unique<FloatMaterialAttribute>(cppName);
			m_MaterialTemplate.AddAttribute(attribute);
			break;
		}
		default:
			break;
		}
	}

	m_IsMaterialTemplateInitialized = true;
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
