#include "ShaderRegistry.h"

#include "Shader.h"

void ShaderRegistry::Register(ShadingModel shadingModel, Shader& shader)
{
	m_Shaders.emplace(shadingModel, shader);
}

Shader* ShaderRegistry::FindShader(ShadingModel shadingModel)
{
	auto it = m_Shaders.find(shadingModel);
	if (it == m_Shaders.end())
	{
		return nullptr;
	}

	return &it->second;
}
