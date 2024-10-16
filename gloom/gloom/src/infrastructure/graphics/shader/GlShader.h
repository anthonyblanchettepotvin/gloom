#pragma once

#include <string>
#include <vector>

#include "../../../engine/graphics/shader/Shader.h"

class GlUniformBufferRegistry;

class GlShader : public Shader
{
public:
	GlShader() = default;
	GlShader(const std::string& vertexShader, const std::string& fragmentShader);

	void Use();
	void Free();

	void SetBool(const std::string& name, bool value) override;
	void SetInt(const std::string& name, int value) override;
	void SetFloat(const std::string& name, float value) override;
	void SetFloatVec3(const std::string& name, const glm::vec3& value) override;
	void SetFloatMat3(const std::string& name, const glm::mat3& value) override;
	void SetFloatMat4(const std::string& name, const glm::mat4& value) override;

	void BindToUniformBuffers(const GlUniformBufferRegistry& uniformBuffer);

	void InitializeMaterialTemplate() override;

private:
	void Initialize();
	void InitializeUniformBufferNames();

	unsigned int CompileVertexShader();
	unsigned int CompileFragmentShader();

	unsigned int LinkShaders(unsigned int vertexShaderId, unsigned int fragmentShaderId);

	unsigned int m_Id = 0;

	std::string m_VertexShader;
	std::string m_FragmentShader;

	std::vector<std::string> m_UniformBufferNames;
};
