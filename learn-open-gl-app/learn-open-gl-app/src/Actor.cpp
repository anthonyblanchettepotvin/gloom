#include "Actor.h"

#include <iostream>

#include <glm/ext/matrix_transform.hpp>

Actor::Actor(const glm::vec3& position, Model* model)
	: position(position), model(model)
{
}

void Actor::Draw(Shader& shader)
{
	if (model)
	{
		shader.setFloatMat4("modelXform", GetModelTransformationMatrix());
		shader.setFloatMat3("normalXform", GetNormalTransformationMatrix());

		model->Draw(shader);
	}
	else
	{
		std::cerr << "ERROR::ACTOR::DRAW::" << "Couldn't draw actor " << this << std::endl;
	}
}

glm::mat4 Actor::GetModelTransformationMatrix()
{
	/* Here, we create our model transformation matrix. This will allows us to transform the
	model vertices which are in local space coordinates into world space coordinates. */
	/* Note that the actual transformation order should be read in reverse: even though in
	code we first translate and then later rotate, the actual transformations first apply
	a rotation and then a translation. The recommended order is: scaling, rotation and then
	translation. Otherwise, the transformations would affect each other in unexpected ways, like
	the translation being scaled. */
	/* Note that glm::value_ptr call is important since glm may store the data
	in a way that doesn't always match OpenGL's expectations. */
	glm::mat4 modelTransformationMatrix = glm::mat4(1.0f);
	modelTransformationMatrix = glm::translate(modelTransformationMatrix, position);

	return modelTransformationMatrix;
}

glm::mat3 Actor::GetNormalTransformationMatrix()
{
	/* Here, we create our normal transformation matrix. Since our normals are hard-coded
	data within the vertices data, we need to transform the normals if we apply a scaling or rotation
	transformation on the cube. */
	/* Note that we don't care about the translation, since normals are directions. That's why we
	convert the 4x4 matrix into a 3x3 matrix -- to remove the translation. */
	/* Note that if we apply a non-uniform scaling transformation, the normals may not be
	perpendicular to the surface anymore. We then inverse then transpose the model matrix
	that our normal transformation matrix is based on. */
	/* See https://learnopengl.com/Lighting/Basic-Lighting for more details. */
	glm::mat3 normalTransformationMatrix = glm::transpose(glm::inverse(GetModelTransformationMatrix()));

	return normalTransformationMatrix;
}
