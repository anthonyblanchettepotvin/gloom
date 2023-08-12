#pragma once

#include <unordered_map>

#include "../../../engine/graphics/shader/Shader.h"

#define MAX_UNIFORM_NAME_LENGTH 32

#define MATERIAL_STRUCT_NAME "material"

class GlShader : public Shader
{
public:
	GlShader(unsigned int id);

	void InitializeMaterialTemplate() override;

	void Use() override;

	void SetBool(const std::string& name, bool value) override;
	void SetInt(const std::string& name, int value) override;
	void SetFloat(const std::string& name, float value) override;
	void SetFloatVec3(const std::string& name, glm::vec3 value) override;
	void SetFloatMat3(const std::string& name, glm::mat3 value) override;
	void SetFloatMat4(const std::string& name, glm::mat4 value) override;

	void BindToGlobalData(GlobalData& globalData) override;

private:
	unsigned int m_Id;
};
