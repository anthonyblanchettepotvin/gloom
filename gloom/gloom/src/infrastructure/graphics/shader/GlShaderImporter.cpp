#include "GlShaderImporter.h"

#include <iostream>
#include <sstream>

#include <glad/glad.h>

#include "../../../engine/EngineGlobals.h"

#include "GlShader.h"

const std::string START_VERTEX_SHADER_TOKEN = "START_VERTEX_SHADER";
const std::string END_VERTEX_SHADER_TOKEN = "END_VERTEX_SHADER";

const std::string START_FRAGMENT_SHADER_TOKEN = "START_FRAGMENT_SHADER";
const std::string END_FRAGMENT_SHADER_TOKEN = "END_FRAGMENT_SHADER";

std::unique_ptr<GlShader> GlShaderImporter::Import(const std::string& filePath)
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
	catch (std::exception e)
	{
		std::stringstream ss;
		ss << "Could not import shader " << filePath << ".";
		gLogErrorMessage(ss.str());

		return nullptr;
	}

	vertexShader = AssembleShader({ version, vertexShader });
	fragmentShader = AssembleShader({ version, fragmentShader });

	return std::make_unique<GlShader>(vertexShader, fragmentShader);
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
