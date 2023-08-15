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
	void Register(const ShadingModel& shadingModel, Shader& shader);

	Shader* FindShader(const ShadingModel& shadingModel) const;

private:
	std::unordered_map<ShadingModel, Shader&> m_Shaders;
};
