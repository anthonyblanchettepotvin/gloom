#pragma once

#include <unordered_map>

#include "../../../engine/graphics/shader/Shader.h"

#define MAX_UNIFORM_NAME_LENGTH 32

#define MATERIAL_STRUCT_NAME "material"

class GlShader : public Shader
{
public:
	GlShader() = default;
	GlShader(const std::string& vertexShader, const std::string& fragmentShader);

	void Use();

	void SetBool(const std::string& name, bool value) override;
	void SetInt(const std::string& name, int value) override;
	void SetFloat(const std::string& name, float value) override;
	void SetFloatVec3(const std::string& name, glm::vec3 value) override;
	void SetFloatMat3(const std::string& name, glm::mat3 value) override;
	void SetFloatMat4(const std::string& name, glm::mat4 value) override;

	void InitializeMaterialTemplate() override;
	void BindToGlobalData(GlobalData& globalData) override;

private:
	unsigned int m_Id = 0;

	std::string m_VertexShader;
	std::string m_FragmentShader;

	void Initialize();

	unsigned int CompileVertexShader();
	unsigned int CompileFragmentShader();

	unsigned int LinkShaders(unsigned int vertexShaderId, unsigned int fragmentShaderId);
};
