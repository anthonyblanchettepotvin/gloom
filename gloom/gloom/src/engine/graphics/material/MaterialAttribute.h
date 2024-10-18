#pragma once

#include <memory>
#include <string>

class MaterialAttributeTemplateBase;

class MaterialAttributeBase
{
public:
	virtual const MaterialAttributeTemplateBase& GetMaterialAttributeTemplate() const = 0;
};

class MaterialAttributeTemplateBase
{
public:
	MaterialAttributeTemplateBase(const std::string& name);

	virtual std::unique_ptr<MaterialAttributeBase> InstantiateMaterialAttribute() const = 0;

	std::string GetName() const { return m_Name; }

protected:
	std::string m_Name;
};

template<typename ValueT>
class MaterialAttributeTemplate : public MaterialAttributeTemplateBase
{
public:
	MaterialAttributeTemplate(const std::string& name);

	std::unique_ptr<MaterialAttributeBase> InstantiateMaterialAttribute() const override;
};

template<typename ValueT>
class MaterialAttribute : public MaterialAttributeBase
{
public:
	MaterialAttribute(const MaterialAttributeTemplate<ValueT>& materialAttributeTemplate);

	const MaterialAttributeTemplate<ValueT>& GetMaterialAttributeTemplate() const override { return m_MaterialAttributeTemplate; }

	void SetValue(const ValueT& value) { m_Value = value; }
	ValueT GetValue() { return m_Value; }
	const ValueT GetValue() const { return m_Value; }

protected:
	ValueT m_Value;

	const MaterialAttributeTemplate<ValueT>& m_MaterialAttributeTemplate;
};

template<typename ValueT>
inline MaterialAttributeTemplate<ValueT>::MaterialAttributeTemplate(const std::string& name)
	: MaterialAttributeTemplateBase(name)
{
}

template<typename ValueT>
inline std::unique_ptr<MaterialAttributeBase> MaterialAttributeTemplate<ValueT>::InstantiateMaterialAttribute() const
{
	return std::make_unique<MaterialAttribute<ValueT>>(*this);
}

template<typename ValueT>
inline MaterialAttribute<ValueT>::MaterialAttribute(const MaterialAttributeTemplate<ValueT>& materialAttributeTemplate)
	: m_MaterialAttributeTemplate(materialAttributeTemplate)
{
}
