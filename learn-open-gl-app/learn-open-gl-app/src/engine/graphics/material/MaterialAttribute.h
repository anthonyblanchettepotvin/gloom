#pragma once

#include <string>
#include <memory>

class Shader;

class MaterialAttribute
{
public:
	MaterialAttribute(const std::string& name);
	virtual ~MaterialAttribute() = default;

	virtual void Set(Shader& shader) const = 0;

	virtual std::unique_ptr<MaterialAttribute> CreateAttributeInstance() const = 0;

	std::string GetName() const { return m_Name; }

protected:
	std::string m_Name;
};
