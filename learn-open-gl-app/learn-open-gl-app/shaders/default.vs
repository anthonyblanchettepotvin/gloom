#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoords;

out vec3 passedColor;
out vec2 passedTexCoords;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1.0f);
	passedColor = color;
	passedTexCoords = texCoords;
}
