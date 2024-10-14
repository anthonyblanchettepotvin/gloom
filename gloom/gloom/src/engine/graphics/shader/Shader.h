#pragma once

#include <string>

#include <glm/glm.hpp>

#include "../../object/Object.h"

#include "../material/MaterialTemplate.h"

class Shader : public Object
{
public:
	Shader();

	virtual void SetBool(const std::string& name, bool value) = 0;
	virtual void SetInt(const std::string& name, int value) = 0;
	virtual void SetFloat(const std::string& name, float value) = 0;
	virtual void SetFloatVec3(const std::string& name, const glm::vec3& value) = 0;
	virtual void SetFloatMat3(const std::string& name, const glm::mat3& value) = 0;
	virtual void SetFloatMat4(const std::string& name, const glm::mat4& value) = 0;

	virtual void InitializeMaterialTemplate() = 0;
	virtual Material* CreateMaterialInstance();

protected:
	bool m_IsMaterialTemplateInitialized = false;
	MaterialTemplate m_MaterialTemplate;
};
