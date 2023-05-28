#pragma once

#include <glm/glm.hpp>

#include <string>

class Shader
{
public:
	unsigned int id;

	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	std::string GetVertexShaderPath() { return vertexShaderPath; };
	std::string GetFragmentShaderPath() { return fragmentShaderPath; };

	void use();

	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setFloatVec3(const std::string& name, glm::vec3 value);
	void setFloatMat3(const std::string& name, glm::mat3 value);
	void setFloatMat4(const std::string& name, glm::mat4 value);

private:
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
};
