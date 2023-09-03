#pragma once

#include <unordered_map>

class Shader;

enum class ShadingModel
{
	Phong
};

class ShaderRegistry
{
public:
	void Register(ShadingModel shadingModel, Shader& shader);

	Shader& FindShader(ShadingModel shadingModel);

private:
	std::unordered_map<ShadingModel, Shader&> m_Shaders;
};
