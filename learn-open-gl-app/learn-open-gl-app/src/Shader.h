#pragma once

#include <glm/glm.hpp>

#include <string>

class Shader
{
public:
	unsigned int id;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setFloatVec3(const std::string& name, glm::vec3 value);
	void setFloatMat3(const std::string& name, glm::mat3 value);
	void setFloatMat4(const std::string& name, glm::mat4 value);
};
