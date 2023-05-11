#version 330 core

in vec3 passedTexCoords;

uniform samplerCube cubemap_skybox;

out vec4 color;

void main()
{
	color = texture(cubemap_skybox, passedTexCoords);
}
