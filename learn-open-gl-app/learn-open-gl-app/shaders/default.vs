#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 passedFragmentWorldPos;
out vec3 passedNormal;
out vec2 passedTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalXform;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	passedFragmentWorldPos = vec3(model * vec4(position, 1.0));
	passedNormal = normalXform * normal;
	passedTexCoords = texCoords;
}
