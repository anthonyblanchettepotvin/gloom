#include "PhongMaterial.h"

void PhongMaterial::Use(Shader* shader)
{
	if (shader)
	{
		shader->SetTexture("material.texture_diffuse1", diffuseTexture);
		shader->SetTexture("material.texture_specular1", specularTexture);
	}
}
