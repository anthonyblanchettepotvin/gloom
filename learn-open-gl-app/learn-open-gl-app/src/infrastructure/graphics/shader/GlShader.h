#pragma once

#include <unordered_map>

#include "../../../game/asset/shader/Shader.h"

#include "../texture/GlCubemap.h"
#include "../texture/GlTexture.h"

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

	void SetTexture(const std::string& name, Texture* texture) override;
	void SetCubemap(const std::string& name, Cubemap* cubemap) override;

	void BindToGlobalData(GlobalData* globalData) override;

private:
	unsigned int m_Id;

	unsigned int m_SamplerIndex;
};
