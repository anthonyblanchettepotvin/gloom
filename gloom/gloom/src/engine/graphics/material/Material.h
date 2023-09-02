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
	T* FindAttribute(const std::string& name);
	template<class T>
	const T* FindAttribute(const std::string& name) const;

	Shader* GetShader() { return m_Shader; }

	std::vector<const MaterialAttribute*> GetAttributes() const;

private:
	Shader* m_Shader = nullptr;

	std::vector<std::unique_ptr<MaterialAttribute>> m_Attributes;

	template<class T, class Self>
	friend T* FindAttributeImpl(Self& self, const std::string& name);
};

template<class T, class Self>
inline T* FindAttributeImpl(Self& self, const std::string& name)
{
	for (const auto& attribute : self.m_Attributes)
	{
		T* typedAttribute = dynamic_cast<T*>(attribute.get());
		if (typedAttribute && attribute->GetName() == name)
		{
			return typedAttribute;
		}
	}

	return nullptr;
}

template<class T>
inline T* Material::FindAttribute(const std::string& name)
{
	return FindAttributeImpl<T>(*this, name);
}

template<class T>
inline const T* Material::FindAttribute(const std::string& name) const
{
	return FindAttributeImpl<const T>(*this, name);
}
