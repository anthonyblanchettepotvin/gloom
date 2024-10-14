#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "../../../engine/graphics/material/MaterialTemplate.h"

class GlUniformBufferRegistry;
class Shader;

class GlShader
{
public:
	GlShader(const Shader& shader);

	void Use();
	void Free();

	void SetBool(const std::string& name, bool value);
	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);
	void SetFloatVec3(const std::string& name, const glm::vec3& value);
	void SetFloatMat3(const std::string& name, const glm::mat3& value);
	void SetFloatMat4(const std::string& name, const glm::mat4& value);

	void BindToUniformBuffers(const GlUniformBufferRegistry& uniformBuffer);

	const MaterialTemplate& GetMaterialTemplate() const { return m_MaterialTemplate; }

private:
	void Initialize();
	void InitializeUniformBufferNames();
	void InitializeMaterialTemplate();

	unsigned int CompileVertexShader();
	unsigned int CompileFragmentShader();

	unsigned int LinkShaders(unsigned int vertexShaderId, unsigned int fragmentShaderId);

	const Shader& m_Shader;

	std::string m_VertexShader;
	std::string m_FragmentShader;

	unsigned int m_Id = 0;

	std::vector<std::string> m_UniformBufferNames;

	MaterialTemplate m_MaterialTemplate;
};
