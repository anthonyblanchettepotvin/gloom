#include "ShaderRegistry.h"

#include <stdexcept>

#include "Shader.h"

#define SHADER_FOR_SHADING_MODEL_NOT_FOUND "Shader for shading model not found."

void ShaderRegistry::Register(ShadingModel shadingModel, Shader& shader)
{
	m_Shaders.emplace(shadingModel, shader);
}

Shader& ShaderRegistry::FindShader(ShadingModel shadingModel)
{
	auto it = m_Shaders.find(shadingModel);
	if (it == m_Shaders.end())
	{
		throw std::runtime_error(SHADER_FOR_SHADING_MODEL_NOT_FOUND);
	}

	return it->second;
}
