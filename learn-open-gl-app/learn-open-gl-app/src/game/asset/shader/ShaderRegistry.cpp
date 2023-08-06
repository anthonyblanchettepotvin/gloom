#include "ShaderRegistry.h"

void ShaderRegistry::Register(const ShadingModel& shadingModel, Shader& shader)
{
	m_Shaders.emplace(shadingModel, shader);
}

Shader* ShaderRegistry::FindShader(const ShadingModel& shadingModel) const
{
	auto it = m_Shaders.find(shadingModel);
	if (it == m_Shaders.end())
		return nullptr;

	return &m_Shaders.at(shadingModel);
}
