#pragma once

#include <string>

#include <glm/glm.hpp>

#include "../../../engine/graphics/globaldata/GlobalData.h"
#include "../../../engine/graphics/material/MaterialTemplate.h"

#include "../Asset.h"

class Shader : public Asset
{
public:
	Shader();

	virtual void InitializeMaterialTemplate() = 0;

	virtual void Use() = 0;

	virtual void SetBool(const std::string& name, bool value) = 0;
	virtual void SetInt(const std::string& name, int value) = 0;
	virtual void SetFloat(const std::string& name, float value) = 0;
	virtual void SetFloatVec3(const std::string& name, glm::vec3 value) = 0;
	virtual void SetFloatMat3(const std::string& name, glm::mat3 value) = 0;
	virtual void SetFloatMat4(const std::string& name, glm::mat4 value) = 0;

	virtual void BindToGlobalData(GlobalData& globalData) = 0;

	virtual Material* CreateMaterialInstance();

protected:
	bool m_IsMaterialTemplateInitialized = false;
	MaterialTemplate m_MaterialTemplate;
};
