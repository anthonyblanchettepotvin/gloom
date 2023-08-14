#include "GlShader.h"

#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "../../../engine/graphics/material/MaterialAttributes.h"

#include "../globaldata/GlGlobalData.h"

GlShader::GlShader(const std::string& vertexShader, const std::string& fragmentShader)
	: m_VertexShader(vertexShader), m_FragmentShader(fragmentShader)
{
	Initialize();
}

void GlShader::InitializeMaterialTemplate()
{
	if (m_Id == 0)
		return;

	GLint nbUniforms;
	glGetProgramiv(m_Id, GL_ACTIVE_UNIFORMS, &nbUniforms);

	GLenum uniformType;
	GLint uniformSize;

	GLchar uniformName[MAX_UNIFORM_NAME_LENGTH];
	GLsizei uniformNameLength;

	for (size_t i = 0; i < nbUniforms; i++)
	{
		glGetActiveUniform(m_Id, (GLint)i, MAX_UNIFORM_NAME_LENGTH, &uniformNameLength, &uniformSize, &uniformType, uniformName);

		std::string attributeName = (std::string)uniformName;

		std::string structName = attributeName.substr(0, attributeName.find_first_of('.'));
		if (structName == MATERIAL_STRUCT_NAME)
		{
			switch (uniformType)
			{
			case GL_FLOAT:
			{
				std::unique_ptr<MaterialAttribute> attribute = std::make_unique<FloatMaterialAttribute>(attributeName);
				m_MaterialTemplate.AddAttribute(attribute);
				break;
			}
			case GL_SAMPLER_2D:
			{
				std::unique_ptr<MaterialAttribute> attribute = std::make_unique<TextureMaterialAttribute>(attributeName);
				m_MaterialTemplate.AddAttribute(attribute);
				break;
			}
			case GL_SAMPLER_CUBE:
			{
				std::unique_ptr<MaterialAttribute> attribute = std::make_unique<CubemapMaterialAttribute>(attributeName);
				m_MaterialTemplate.AddAttribute(attribute);
				break;
			}
			default:
				break;
			}
		}
	}

	m_IsMaterialTemplateInitialized = true;
}

void GlShader::Use()
{
	glUseProgram(m_Id);
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

void GlShader::BindToGlobalData(GlobalData& globalData)
{
	try
	{
		GlGlobalData& glGlobalData = dynamic_cast<GlGlobalData&>(globalData);

		glUniformBlockBinding(m_Id, glGetUniformBlockIndex(m_Id, glGlobalData.GetName().c_str()), glGlobalData.GetIndex());
	}
	catch (std::bad_cast e)
	{
		// TODO: Display error
	}
}

void GlShader::Initialize()
{
	unsigned int vertexShaderId = CompileVertexShader();
	unsigned int fragmentShaderId = CompileFragmentShader();

	m_Id = LinkShaders(vertexShaderId, fragmentShaderId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

unsigned int GlShader::CompileVertexShader()
{
	const char* cVertexShader = m_VertexShader.c_str();

	unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &cVertexShader, NULL);
	glCompileShader(vertexShaderId);

	int success;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);

		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return vertexShaderId;
}

unsigned int GlShader::CompileFragmentShader()
{
	const char* cFragmentShader = m_FragmentShader.c_str();

	unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &cFragmentShader, NULL);
	glCompileShader(fragmentShaderId);

	int success;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);

		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return fragmentShaderId;
}

unsigned int GlShader::LinkShaders(unsigned int vertexShaderId, unsigned int fragmentShaderId)
{
	unsigned int programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	int success;
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(programId, 512, NULL, infoLog);

		std::cout << "ERROR::SHADER::PROGRAM::LIKING_FAILED\n" << infoLog << std::endl;
	}

	return programId;
}
