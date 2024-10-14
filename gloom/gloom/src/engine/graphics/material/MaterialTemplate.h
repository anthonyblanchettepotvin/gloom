#pragma once

#include <memory>
#include <vector>

#include "MaterialAttribute.h"

class Shader;

class MaterialTemplate
{
public:
	MaterialTemplate(const Shader& shader);

	void AddAttribute(std::unique_ptr<MaterialAttributeTemplateBase>& attribute);

	template<class T>
	T* FindAttribute(const std::string& name);
	template<class T>
	const T* FindAttribute(const std::string& name) const;

	const Shader& GetShader() const { return m_Shader; }

	std::vector<const MaterialAttributeTemplateBase*> GetAttributes() const;

private:
	const Shader& m_Shader;

	std::vector<std::unique_ptr<MaterialAttributeTemplateBase>> m_Attributes;

	template<class T, class Self>
	friend T* MaterialTemplate_FindAttributeImpl(Self& self, const std::string& name);
};

template<class T, class Self>
inline T* MaterialTemplate_FindAttributeImpl(Self& self, const std::string& name)
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
inline T* MaterialTemplate::FindAttribute(const std::string& name)
{
	return MaterialTemplate_FindAttributeImpl<T>(*this, name);
}

template<class T>
inline const T* MaterialTemplate::FindAttribute(const std::string& name) const
{
	return MaterialTemplate_FindAttributeImpl<const T>(*this, name);
}
