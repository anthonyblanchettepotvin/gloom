#pragma once

#include <string>
#include <memory>

class Shader;

class MaterialAttribute
{
public:
	MaterialAttribute(const std::string& name);
	virtual ~MaterialAttribute() = default;

	virtual MaterialAttribute* CreateAttributeInstance() const = 0;

	std::string GetName() const { return m_Name; }

protected:
	std::string m_Name;
};
