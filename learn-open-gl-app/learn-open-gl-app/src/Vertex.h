#pragma once

#include <glm/glm.hpp>

class Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;

	Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& textureCoordinates);
};
