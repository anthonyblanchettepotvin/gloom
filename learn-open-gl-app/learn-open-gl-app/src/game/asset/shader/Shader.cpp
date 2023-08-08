#include "Shader.h"

Shader::Shader()
	: m_MaterialTemplate(*this)
{
}

Material* Shader::CreateMaterialInstance()
{
	if (!m_IsMaterialTemplateInitialized)
	{
		InitializeMaterialTemplate();
	}

	return m_MaterialTemplate.CreateMaterialInstance();
}
