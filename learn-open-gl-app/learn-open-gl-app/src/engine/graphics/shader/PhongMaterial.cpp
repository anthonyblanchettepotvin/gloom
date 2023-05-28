#include "PhongMaterial.h"

void PhongMaterial::Bind(Shader* shader)
{
	if (diffuseTexture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTexture->id);

		shader->setInt("material.texture_diffuse1", 0);
	}

	if (specularTexture)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularTexture->id);

		shader->setInt("material.texture_specular1", 1);
	}
}
