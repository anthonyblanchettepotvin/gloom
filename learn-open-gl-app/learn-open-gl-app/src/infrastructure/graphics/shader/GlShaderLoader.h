#pragma once

#include <vector>
#include <fstream>

#include "../../../engine/graphics/shader/ShaderLoader.h"

class GlShaderLoader : public ShaderLoader
{
public:
	Shader* Load(const std::string& path) override;

private:
	std::string ParseVersion(std::ifstream& file);
	std::string ParseVertexShader(std::ifstream& file);
	std::string ParseFragmentShader(std::ifstream& file);

	std::string AssembleShader(const std::vector<std::string>& parts);

	unsigned int CompileVertexShader(const std::string& vertexShader);
	unsigned int CompileFragmentShader(const std::string& fragmentShader);

	unsigned int LinkShaders(unsigned int vertexShaderId, unsigned int fragmentShaderId);
};
