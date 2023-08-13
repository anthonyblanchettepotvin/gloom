#include "GlShaderImporter.h"

#include <iostream>
#include <sstream>

#include <glad/glad.h>

#include "GlShader.h"

const std::string START_VERTEX_SHADER_TOKEN = "START_VERTEX_SHADER";
const std::string END_VERTEX_SHADER_TOKEN = "END_VERTEX_SHADER";

const std::string START_FRAGMENT_SHADER_TOKEN = "START_FRAGMENT_SHADER";
const std::string END_FRAGMENT_SHADER_TOKEN = "END_FRAGMENT_SHADER";

Shader* GlShaderImporter::Import(const std::string& filePath)
{
	std::ifstream shaderFile;

	std::string version;
	std::string vertexShader;
	std::string fragmentShader;

	try
	{
		shaderFile.open(filePath);

		version = ParseVersion(shaderFile);
		vertexShader = ParseVertexShader(shaderFile);
		fragmentShader = ParseFragmentShader(shaderFile);
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR::SHADER::FILE::READING_FAILED\n" << e.what() << std::endl;
	}

	vertexShader = AssembleShader({ version, vertexShader });
	fragmentShader = AssembleShader({ version, fragmentShader });

	unsigned int vertexShaderId = CompileVertexShader(vertexShader);
	unsigned int fragmentShaderId = CompileFragmentShader(fragmentShader);

	unsigned int programId = LinkShaders(vertexShaderId, fragmentShaderId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return new GlShader(programId);
}

std::string GlShaderImporter::ParseVersion(std::ifstream& file)
{
	std::string version;

	std::getline(file, version);

	return version;
}

std::string GlShaderImporter::ParseVertexShader(std::ifstream& file)
{
	std::stringstream vertexShader;

	bool startTokenFound = false;
	bool endTokenFound = false;

	std::string line;
	while (std::getline(file, line))
	{
		if (line == START_VERTEX_SHADER_TOKEN) // FIXME: if line has whitespaces, it won't enter the condition
		{
			startTokenFound = true;
		}
		else if (line == END_VERTEX_SHADER_TOKEN) // FIXME: if line has whitespaces, it won't enter the condition
		{
			endTokenFound = true;

			break;
		}
		else if (startTokenFound && !endTokenFound)
		{
			vertexShader << line << std::endl;
		}
	}

	return vertexShader.str();
}

std::string GlShaderImporter::ParseFragmentShader(std::ifstream& file)
{
	std::stringstream fragmentShader;

	bool startTokenFound = false;
	bool endTokenFound = false;

	std::string line;
	while (std::getline(file, line))
	{
		if (line == START_FRAGMENT_SHADER_TOKEN) // FIXME: if line has whitespaces, it won't enter the condition
		{
			startTokenFound = true;
		}
		else if (line == END_FRAGMENT_SHADER_TOKEN) // FIXME: if line has whitespaces, it won't enter the condition
		{
			endTokenFound = true;

			break;
		}
		else if (startTokenFound && !endTokenFound)
		{
			fragmentShader << line << std::endl;
		}
	}

	return fragmentShader.str();
}

std::string GlShaderImporter::AssembleShader(const std::vector<std::string>& parts)
{
	std::stringstream shader;

	for (const auto& part : parts)
	{
		shader << part;
	}

	return shader.str();
}

unsigned int GlShaderImporter::CompileVertexShader(const std::string& vertexShader)
{
	const char* cVertexShader = vertexShader.c_str();

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

unsigned int GlShaderImporter::CompileFragmentShader(const std::string& fragmentShader)
{
	const char* cFragmentShader = fragmentShader.c_str();

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

unsigned int GlShaderImporter::LinkShaders(unsigned int vertexShaderId, unsigned int fragmentShaderId)
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
