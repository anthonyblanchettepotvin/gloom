#include "GlShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

GlShader::GlShader(unsigned int id)
	: id(id)
{
}

void GlShader::Use()
{
	glUseProgram(id);
}

void GlShader::SetBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void GlShader::SetInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void GlShader::SetFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void GlShader::SetFloatVec3(const std::string& name, glm::vec3 value)
{
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}

void GlShader::SetFloatMat3(const std::string& name, glm::mat3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void GlShader::SetFloatMat4(const std::string& name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void GlShader::SetGlobalDataReference(const std::string& name)
{
	// TODO: This information should be retrieved from a context or something
	unsigned int index = 0;

	if (name == "ubo_matrices")
	{
		index = 0;
	}
	else if (name == "ubo_camera")
	{
		index = 1;
	}
	else if (name == "ubo_lights")
	{
		index = 2;
	}

	glUniformBlockBinding(id, glGetUniformBlockIndex(id, name.c_str()), index);
}
