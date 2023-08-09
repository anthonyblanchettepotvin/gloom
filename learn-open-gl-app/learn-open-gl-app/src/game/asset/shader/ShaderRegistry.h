#pragma once

#include "../../../engine/graphics/shader/Shader.h"

#include <unordered_map>

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
