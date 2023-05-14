#pragma once

#include "Material.h"
#include "Texture.h"

class PhongMaterial : public Material
{
public:
	void Bind(Shader* shader) override;

	void SetDiffuseTexture(Texture* diffuseTexture) { this->diffuseTexture = diffuseTexture; }
	void SetSpecularTexture(Texture* specularTexture) { this->specularTexture = specularTexture; }

private:
	Texture* diffuseTexture;
	Texture* specularTexture;
};
