#version 330 core

in vec3 passedTexCoords;

uniform samplerCube cubemap_skybox;

out vec4 color;

void main()
{
	/* The key difference between a normal texture and a cubemap is that the cubemap
	is sampled using a direction vector instead of coordinates. That said, the cubemap
	vertices' position should always be in local space. */
	color = texture(cubemap_skybox, passedTexCoords);
}
