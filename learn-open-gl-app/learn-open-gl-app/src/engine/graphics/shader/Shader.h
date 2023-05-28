#pragma once

#include <string>

#include <glm/glm.hpp>

class Shader
{
public:
	virtual void Use() = 0;

	virtual void SetBool(const std::string& name, bool value) = 0;
	virtual void SetInt(const std::string& name, int value) = 0;
	virtual void SetFloat(const std::string& name, float value) = 0;
	virtual void SetFloatVec3(const std::string& name, glm::vec3 value) = 0;
	virtual void SetFloatMat3(const std::string& name, glm::mat3 value) = 0;
	virtual void SetFloatMat4(const std::string& name, glm::mat4 value) = 0;

	virtual void SetGlobalDataReference(const std::string& name) = 0;
};
