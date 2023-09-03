#pragma once

#include <glm/glm.hpp>

#include "MaterialAttribute.h"

class Cubemap;
class Texture;

class FloatMaterialAttribute : public MaterialAttribute
{
public:
	FloatMaterialAttribute(const std::string& name);

	MaterialAttribute* CreateAttributeInstance() override;

	void SetValue(float value) { m_Value = value; }
	float GetValue() const { return m_Value; }

private:
	float m_Value = 1.0f;
};

class TextureMaterialAttribute : public MaterialAttribute
{
public:
	TextureMaterialAttribute(const std::string& name);

	MaterialAttribute* CreateAttributeInstance() override;

	void SetValue(Texture* value) { m_Value = value; }
	const Texture* GetValue() const { return m_Value; }

private:
	Texture* m_Value = nullptr;
};

class CubemapMaterialAttribute : public MaterialAttribute
{
public:
	CubemapMaterialAttribute(const std::string& name);

	MaterialAttribute* CreateAttributeInstance() override;

	void SetValue(Cubemap* value) { m_Value = value; }
	const Cubemap* GetValue() const { return m_Value; }

private:
	Cubemap* m_Value = nullptr;
};
