#include "PointLight.h"

#include <glm/ext/matrix_transform.hpp>
#include <iostream>

PointLight::PointLight(const glm::vec3& position, Model* model)
	: position(position), model(model),
	ambientColor(DEFAULT_POINT_LIGHT_AMBIENT_COLOR),
	diffuseColor(DEFAULT_POINT_LIGHT_DIFFUSE_COLOR),
	specularColor(DEFAULT_POINT_LIGHT_SPECULAR_COLOR),
	attenuation(DEFAULT_POINT_LIGHT_ATTENUATION)
{
}

void PointLight::Draw(Shader& shader)
{
	if (model)
	{
		shader.setFloatVec3("lightColor", diffuseColor);
		shader.setFloatMat4("modelXform", GetModelTransformationMatrix());

		model->Draw(shader);
	}
	else
	{
		std::cerr << "ERROR::POINT_LIGHT::DRAW::" << "Couldn't draw point light " << this << std::endl;
	}
}

void PointLight::Register(Shader& shader, const std::string& identifier)
{
	shader.setFloatVec3(identifier + ".position", position);
	shader.setFloatVec3(identifier + ".ambientColor", ambientColor);
	shader.setFloatVec3(identifier + ".diffuseColor", diffuseColor);
	shader.setFloatVec3(identifier + ".specularColor", specularColor);
	shader.setFloat(identifier + ".constant", attenuation.constant);
	shader.setFloat(identifier + ".linear", attenuation.linear);
	shader.setFloat(identifier + ".quadratic", attenuation.quadratic);
}

glm::mat4 PointLight::GetModelTransformationMatrix()
{
	glm::mat4 modelTransformationMatrix = glm::mat4(1.0f);
	modelTransformationMatrix = glm::translate(modelTransformationMatrix, position);
	modelTransformationMatrix = glm::scale(modelTransformationMatrix, glm::vec3(0.2f));

	return modelTransformationMatrix;
}
