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
	std::string ParseVersion(std::ifstream& file) const;
	std::string ParseVertexShader(std::ifstream& file) const;
	std::string ParseFragmentShader(std::ifstream& file) const;

	std::string AssembleShader(const std::vector<std::string>& parts) const;
};
