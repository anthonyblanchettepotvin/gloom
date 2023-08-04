#pragma once

#include <string>

#include <glm/glm.hpp>

#include "../../../engine/graphics/globaldata/GlobalData.h"
#include "../../../engine/graphics/texture/Cubemap.h"
#include "../../../game/asset/texture/Texture.h"

#include "../Asset.h"

class Shader : public Asset
{
public:
	virtual void Use() = 0;

	virtual void SetBool(const std::string& name, bool value) = 0;
	virtual void SetInt(const std::string& name, int value) = 0;
	virtual void SetFloat(const std::string& name, float value) = 0;
	virtual void SetFloatVec3(const std::string& name, glm::vec3 value) = 0;
	virtual void SetFloatMat3(const std::string& name, glm::mat3 value) = 0;
	virtual void SetFloatMat4(const std::string& name, glm::mat4 value) = 0;

	virtual void SetTexture(const std::string& name, Texture* texture) = 0;
	virtual void SetCubemap(const std::string& name, Cubemap* cubemap) = 0;

	virtual void BindToGlobalData(GlobalData* globalData) = 0;
};
