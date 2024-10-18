#include "GlShaderParser.h"

#include <glad/glad.h>

#include <tuple>

const std::string START_VERTEX_SHADER_TOKEN = "START_VERTEX_SHADER";
const std::string END_VERTEX_SHADER_TOKEN = "END_VERTEX_SHADER";

const std::string START_FRAGMENT_SHADER_TOKEN = "START_FRAGMENT_SHADER";
const std::string END_FRAGMENT_SHADER_TOKEN = "END_FRAGMENT_SHADER";

std::tuple<std::string, std::string> GlShaderParser::Parse(const std::string& code)
{
	std::stringstream codeBuf(code);

	std::string version = ParseVersion(codeBuf);
	std::string vertexShader = ParseVertexShader(codeBuf);
	std::string fragmentShader = ParseFragmentShader(codeBuf);

	vertexShader = AssembleShader({ version, vertexShader });
	fragmentShader = AssembleShader({ version, fragmentShader });

	return std::make_tuple(vertexShader, fragmentShader);
}

std::string GlShaderParser::ParseVersion(std::stringstream& codeBuf)
{
	std::string version;

	std::getline(codeBuf, version);

	return version;
}

std::string GlShaderParser::ParseVertexShader(std::stringstream& codeBuf)
{
	std::stringstream vertexShader;

	bool startTokenFound = false;
	bool endTokenFound = false;

	std::string line;
	while (std::getline(codeBuf, line))
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

std::string GlShaderParser::ParseFragmentShader(std::stringstream& codeBuf)
{
	std::stringstream fragmentShader;

	bool startTokenFound = false;
	bool endTokenFound = false;

	std::string line;
	while (std::getline(codeBuf, line))
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

std::string GlShaderParser::AssembleShader(const std::vector<std::string>& parts)
{
	std::stringstream shader;

	for (const auto& part : parts)
	{
		shader << part;
	}

	return shader.str();
}
