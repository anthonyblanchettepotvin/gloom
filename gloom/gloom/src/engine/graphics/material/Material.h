#pragma once

#include <memory>
#include <vector>

#include "../../object/Object.h"

#include "MaterialAttribute.h"

class MaterialTemplate;

class Material : public Object
{
public:
	Material() = default;
	Material(const MaterialTemplate* materialTemplate);

	template<class T>
	T* FindAttribute(const std::string& name);
	template<class T>
	const T* FindAttribute(const std::string& name) const;

	void SetMaterialTemplate(const MaterialTemplate* materialTemplate);
	const MaterialTemplate* const GetMaterialTemplate() const { return m_MaterialTemplate; }

	std::vector<const MaterialAttributeBase*> GetAttributes() const;

private:
	void ResetAttributes();

	const MaterialTemplate* m_MaterialTemplate = nullptr;

	std::vector<std::unique_ptr<MaterialAttributeBase>> m_Attributes;

	template<class T, class Self>
	friend T* Material_FindAttributeImpl(Self& self, const std::string& name);
};

template<class T, class Self>
inline T* Material_FindAttributeImpl(Self& self, const std::string& name)
{
	for (const auto& attribute : self.m_Attributes)
	{
		T* typedAttribute = dynamic_cast<T*>(attribute.get());
		if (typedAttribute && attribute->GetMaterialAttributeTemplate().GetName() == name)
		{
			return typedAttribute;
		}
	}

	return nullptr;
}

template<class T>
inline T* Material::FindAttribute(const std::string& name)
{
	return Material_FindAttributeImpl<T>(*this, name);
}

template<class T>
inline const T* Material::FindAttribute(const std::string& name) const
{
	return Material_FindAttributeImpl<const T>(*this, name);
}
