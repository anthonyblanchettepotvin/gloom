#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 passedFragmentWorldPos;
out vec3 passedNormal;
out vec2 passedTexCoords;

uniform mat4 modelXform;
uniform mat4 viewXform;
uniform mat4 projectionXform;
uniform mat3 normalXform;

void main()
{
	gl_Position = projectionXform * viewXform * modelXform * vec4(position, 1.0);

	passedFragmentWorldPos = vec3(modelXform * vec4(position, 1.0));
	passedNormal = normalXform * normal;
	passedTexCoords = texCoords;
}
