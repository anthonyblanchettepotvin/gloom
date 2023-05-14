#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 modelXform;
uniform mat4 viewXform;
uniform mat4 projectionXform;
uniform mat3 normalXform;

out vec3 passed_position;
out vec3 passed_normal;

void main()
{
	gl_Position = projectionXform * viewXform * modelXform * vec4(position, 1.0);

	passed_position = vec3(modelXform * vec4(position, 1.0));
	passed_normal = normalXform * normal;
}
