#pragma once

#include <string>

class MaterialAttribute
{
public:
	MaterialAttribute(const std::string& name);

	virtual MaterialAttribute* CreateAttributeInstance() const = 0;

	std::string GetName() const { return m_Name; }

protected:
	std::string m_Name;
};
