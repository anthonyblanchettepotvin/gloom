#pragma once

#include <fstream>
#include <vector>

class Shader;

class GlShaderImporter
{
public:
	Shader* Import(const std::string& filePath);

private:
	std::string ParseVersion(std::ifstream& file);
	std::string ParseVertexShader(std::ifstream& file);
	std::string ParseFragmentShader(std::ifstream& file);

	std::string AssembleShader(const std::vector<std::string>& parts);

	unsigned int CompileVertexShader(const std::string& vertexShader);
	unsigned int CompileFragmentShader(const std::string& fragmentShader);

	unsigned int LinkShaders(unsigned int vertexShaderId, unsigned int fragmentShaderId);
};
