#pragma once

#include "Material.h"

#include "../texture/Texture.h"

class PhongMaterial : public Material
{
public:
	void SetDiffuseTexture(Texture* diffuseTexture) { this->diffuseTexture = diffuseTexture; }
	void SetSpecularTexture(Texture* specularTexture) { this->specularTexture = specularTexture; }

	void Use(Shader* shader) override;

protected:
	Texture* diffuseTexture;
	Texture* specularTexture;
};
