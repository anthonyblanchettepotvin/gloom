#pragma once

#include <fstream>
#include <memory>
#include <vector>

class GlShader;

class GlShaderImporter
{
public:
	std::unique_ptr<GlShader> Import(const std::string& filePath);

private:
	std::string ParseVersion(std::ifstream& file);
	std::string ParseVertexShader(std::ifstream& file);
	std::string ParseFragmentShader(std::ifstream& file);

	std::string AssembleShader(const std::vector<std::string>& parts);
};
