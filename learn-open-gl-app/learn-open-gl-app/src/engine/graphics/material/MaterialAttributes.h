#pragma once

#include <glm/glm.hpp>

#include "../../../game/asset/cubemap/Cubemap.h"
#include "../../../game/asset/texture/Texture.h"

#include "MaterialAttribute.h"

class FloatMaterialAttribute : public MaterialAttribute
{
public:
	FloatMaterialAttribute(const std::string& name);

	float GetValue() const { return m_Value; }
	void SetValue(float value) { m_Value = value; }

	MaterialAttribute* CreateAttributeInstance() const override;

private:
	float m_Value = 1.0f;
};

class TextureMaterialAttribute : public MaterialAttribute
{
public:
	TextureMaterialAttribute(const std::string& name);

	Texture* GetValue() const { return m_Value; }
	void SetValue(Texture* value) { m_Value = value; }

	MaterialAttribute* CreateAttributeInstance() const override;

private:
	Texture* m_Value = nullptr;
};

class CubemapMaterialAttribute : public MaterialAttribute
{
public:
	CubemapMaterialAttribute(const std::string& name);

	Cubemap* GetValue() const { return m_Value; }
	void SetValue(Cubemap* value) { m_Value = value; }

	MaterialAttribute* CreateAttributeInstance() const override;

private:
	Cubemap* m_Value = nullptr;
};
