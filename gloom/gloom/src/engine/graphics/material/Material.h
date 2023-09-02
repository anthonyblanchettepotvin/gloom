#pragma once

#include <memory>
#include <vector>

#include "../../object/Object.h"

#include "MaterialAttribute.h"

class Shader;

class Material : public Object
{
public:
	Material() = default;
	Material(Shader* shader, std::vector<std::unique_ptr<MaterialAttribute>>& attributes);

	template<class T>
	T* FindAttribute(const std::string& name) const;

	Shader* GetShader() { return m_Shader; }

	std::vector<const MaterialAttribute*> GetAttributes() const;
	
private:
	Shader* m_Shader = nullptr;

	std::vector<std::unique_ptr<MaterialAttribute>> m_Attributes;
};

template<class T>
inline T* Material::FindAttribute(const std::string& name) const
{
	for (const auto& attribute : m_Attributes)
	{
		T* typedAttribute = dynamic_cast<T*>(attribute.get());
		if (typedAttribute && attribute->GetName() == name)
		{
			return typedAttribute;
		}
	}

	return nullptr;
}
