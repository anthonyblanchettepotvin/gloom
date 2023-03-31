#include "Vertex.h"

Vertex::Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& textureCoordinates)
	: position(position), normal(normal), textureCoordinates(textureCoordinates)
{
}
