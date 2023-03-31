#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		std::stringstream vertexShaderStream, fragmentShaderStream;

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (const std::exception&)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	const char* cVertexCode = vertexCode.c_str();
	const char* cFragmentCode = fragmentCode.c_str();

	unsigned int vertexId, fragmentId;
	int success;
	char infoLog[512];

	/* Here, we compile our vertex shader (yes, at run-time). */
	vertexId = glCreateShader(GL_VERTEX_SHADER);
	/* The following function binds the vertex shader source to the vertex shader object.
	The second arguments specifies the number of strings we're passing as source code. */
	glShaderSource(vertexId, 1, &cVertexCode, NULL);
	glCompileShader(vertexId);
	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
	/* Here, we're just making sure the compilation was successful. If not, we print the error. */
	if (!success) {
		glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* Here, we compile our fragment shader using the same exact process which we used
	for compiling the vertex shader. The only difference is that we use GL_FRAGMENT_SHADER
	as the shader type instead of GL_VERTEX_SHADER. */
	fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentId, 1, &cFragmentCode, NULL);
	glCompileShader(fragmentId);
	glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* Here, we link the vertex and the fragment shaders into a shader program object.
	We can then use this shader program object during our rendering process. */
	id = glCreateProgram();
	glAttachShader(id, vertexId);
	glAttachShader(id, fragmentId);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	/* Here, we're just making sure the linking was successful. If not, we print the error. */
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	/* The shaders are linked in the shader program, so we don't need them anymore. */
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

void Shader::use()
{
	glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloatVec3(const std::string& name, glm::vec3 value)
{
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setFloatMat3(const std::string& name, glm::mat3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setFloatMat4(const std::string& name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
