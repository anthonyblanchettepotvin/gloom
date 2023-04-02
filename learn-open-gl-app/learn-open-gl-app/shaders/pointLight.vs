#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 modelXform;
uniform mat4 viewXform;
uniform mat4 projectionXform;

void main()
{
	gl_Position = projectionXform * viewXform * modelXform * vec4(position, 1.0);
}
