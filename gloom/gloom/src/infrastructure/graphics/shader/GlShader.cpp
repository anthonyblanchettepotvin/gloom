#include "GlShader.h"

#include <memory>
#include <sstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "../../../engine/EngineGlobals.h"
#include "../../../engine/graphics/cubemap/Cubemap.h"
#include "../../../engine/graphics/material/MaterialAttribute.h"
#include "../../../engine/graphics/shader/Shader.h"
#include "../../../engine/graphics/texture/Texture.h"

#include "../uniformbuffer/GlUniformBuffer.h"
#include "../uniformbuffer/GlUniformBufferRegistry.h"

#include "GlShaderParser.h"

#define MAX_UNIFORM_NAME_BUF_LENGTH 32
#define MAX_UNIFORM_BLOCK_NAME_BUF_LENGTH 32

#define MATERIAL_STRUCT_NAME "material"

GlShader::GlShader(const Shader& shader)
	: m_Shader(shader), m_MaterialTemplate(shader)
{
	Initialize();
}

void GlShader::Use()
{
	glUseProgram(m_Id);
}

void GlShader::Free()
{
	glUseProgram(0);
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

void GlShader::SetFloatVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(m_Id, name.c_str()), 1, glm::value_ptr(value));
}

void GlShader::SetFloatMat3(const std::string& name, const glm::mat3& value)
{
	glUniformMatrix3fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void GlShader::SetFloatMat4(const std::string& name, const glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void GlShader::BindToUniformBuffers(const GlUniformBufferRegistry& uniformBufferRegistry)
{
	for (const auto& uniformBufferName : m_UniformBufferNames)
	{
		const GlUniformBuffer* uniformBuffer = uniformBufferRegistry.FindUniformBufferByName(uniformBufferName);
		if (!uniformBuffer)
		{
			std::stringstream ss;
			ss << "Binding to uniform buffer failed:\n" << uniformBufferName << " was not found in the uniform buffer registry.";
			gLogErrorMessage(ss.str());

			continue;
		}

		glUniformBlockBinding(m_Id, glGetUniformBlockIndex(m_Id, uniformBuffer->GetName().c_str()), uniformBuffer->GetIndex());
	}
}

void GlShader::Initialize()
{
	std::tuple<std::string, std::string> parsedShader = GlShaderParser::Parse(m_Shader.GetCode());
	m_VertexShader = std::get<0>(parsedShader);
	m_FragmentShader = std::get<1>(parsedShader);

	unsigned int vertexShaderId = CompileVertexShader();
	unsigned int fragmentShaderId = CompileFragmentShader();

	m_Id = LinkShaders(vertexShaderId, fragmentShaderId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	InitializeUniformBufferNames();
	InitializeMaterialTemplate();
}

void GlShader::InitializeUniformBufferNames()
{
	if (m_Id == 0)
	{
		return;
	}

	GLint nbUniformBlocks;
	glGetProgramiv(m_Id, GL_ACTIVE_UNIFORM_BLOCKS, &nbUniformBlocks);

	GLchar uniformBlockNameBuf[MAX_UNIFORM_BLOCK_NAME_BUF_LENGTH];
	GLsizei uniformBlockNameBufLength;

	for (size_t i = 0; i < nbUniformBlocks; i++)
	{
		glGetActiveUniformBlockName(m_Id, (GLint)i, MAX_UNIFORM_BLOCK_NAME_BUF_LENGTH, &uniformBlockNameBufLength, uniformBlockNameBuf);

		std::string uniformBlockName = (std::string)uniformBlockNameBuf;

		m_UniformBufferNames.push_back(uniformBlockName);
	}
}

void GlShader::InitializeMaterialTemplate()
{
	if (m_Id == 0)
	{
		return;
	}

	GLint nbUniforms;
	glGetProgramiv(m_Id, GL_ACTIVE_UNIFORMS, &nbUniforms);

	GLenum uniformType;
	GLint uniformSize;

	GLchar uniformNameBuf[MAX_UNIFORM_NAME_BUF_LENGTH];
	GLsizei uniformNameBufLength;

	for (size_t i = 0; i < nbUniforms; i++)
	{
		glGetActiveUniform(m_Id, (GLint)i, MAX_UNIFORM_NAME_BUF_LENGTH, &uniformNameBufLength, &uniformSize, &uniformType, uniformNameBuf);

		std::string attributeName = (std::string)uniformNameBuf;

		std::string structName = attributeName.substr(0, attributeName.find_first_of('.'));
		if (structName == MATERIAL_STRUCT_NAME)
		{
			switch (uniformType)
			{
			case GL_FLOAT:
			{
				std::unique_ptr<MaterialAttributeTemplateBase> attribute = std::make_unique<MaterialAttributeTemplate<float>>(attributeName);
				m_MaterialTemplate.AddAttribute(attribute);
				break;
			}
			case GL_SAMPLER_2D:
			{
				std::unique_ptr<MaterialAttributeTemplateBase> attribute = std::make_unique<MaterialAttributeTemplate<Texture*>>(attributeName);
				m_MaterialTemplate.AddAttribute(attribute);
				break;
			}
			case GL_SAMPLER_CUBE:
			{
				std::unique_ptr<MaterialAttributeTemplateBase> attribute = std::make_unique<MaterialAttributeTemplate<Cubemap*>>(attributeName);
				m_MaterialTemplate.AddAttribute(attribute);
				break;
			}
			default:
				break;
			}
		}
	}
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

		std::stringstream ss;
		ss << "Vertex shader compilation failed:\n" << infoLog;
		gLogErrorMessage(ss.str());
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

		std::stringstream ss;
		ss << "Fragment shader compilation failed:\n" << infoLog;
		gLogErrorMessage(ss.str());
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

		std::stringstream ss;
		ss << "Shader program linking failed:\n" << infoLog;
		gLogErrorMessage(ss.str());
	}

	return programId;
}
