#pragma once

#include "../../../engine/graphics/shader/Shader.h"

class GlShader : public Shader
{
public:
	GlShader(unsigned int id);

	void Use() override;

	void SetBool(const std::string& name, bool value) override;
	void SetInt(const std::string& name, int value) override;
	void SetFloat(const std::string& name, float value) override;
	void SetFloatVec3(const std::string& name, glm::vec3 value) override;
	void SetFloatMat3(const std::string& name, glm::mat3 value) override;
	void SetFloatMat4(const std::string& name, glm::mat4 value) override;

	void SetGlobalDataReference(const std::string& name) override;

private:
	unsigned int id;
};
