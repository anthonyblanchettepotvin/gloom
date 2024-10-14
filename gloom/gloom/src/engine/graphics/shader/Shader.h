#pragma once

#include "../../object/Object.h"

class Shader : public Object
{
public:
	Shader() = default;
	Shader(const std::string& code);

	std::string GetCode() const { return m_Code; }

private:
	std::string m_Code;
};
