#pragma once

#include <memory>
#include <vector>
#include <type_traits>

#include "MaterialAttribute.h"

class Shader;

class Material
{
public:
	Material(Shader& shader, std::vector<std::unique_ptr<MaterialAttribute>>& attributes);

	virtual void Use();

	Shader& GetShader() const { return m_Shader; }

	template<class T>
	T* FindAttribute(const std::string& name) const;
	
private:
	Shader& m_Shader;

	std::vector<std::unique_ptr<MaterialAttribute>> m_Attributes;
};

template<class T>
inline T* Material::FindAttribute(const std::string& name) const
{
	for (const auto& attribute : m_Attributes)
	{
		T* typedAttribute = dynamic_cast<T*>(attribute.get());
		if (typedAttribute && attribute.get()->GetName() == name)
			return typedAttribute;
	}

	return nullptr;
}
