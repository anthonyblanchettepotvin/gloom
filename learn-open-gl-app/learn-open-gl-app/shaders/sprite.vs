#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

uniform mat4 modelXform;
uniform mat4 viewXform;
uniform mat4 projectionXform;

out vec2 passedTexCoords;

void main()
{
	gl_Position = projectionXform * viewXform * modelXform * vec4(position, 1.0);

	passedTexCoords = texCoords;
}
