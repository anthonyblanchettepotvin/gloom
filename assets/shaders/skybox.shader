#version 330 core

START_VERTEX_SHADER

layout(location = 0) in vec3 position;

layout(std140) uniform ubo_matrices{
	mat4 view;
	mat4 skybox;
	mat4 projection;
};

out VS_OUT{
	vec3 texCoords;
} vs_out;

void main()
{
	vec4 tempPosition = projection * skybox * vec4(position, 1.0);

	/* We set the gl_Position z value to the w value. When the perspective division is applied
	right after the vertex shader has run, the resulting z component will always be equal to 1.0,
	since w / w = 1.0, which is the maximum depth value. Remember that we want the skybox to be
	behind everything in the scene. */
	gl_Position = tempPosition.xyww;

	vs_out.texCoords = position;
}

END_VERTEX_SHADER

START_FRAGMENT_SHADER

struct Material {
	samplerCube cubemap_skybox;
};

in VS_OUT{
	vec3 texCoords;
} fs_in;

uniform Material material;

out vec4 color;

void main()
{
	/* The key difference between a normal texture and a cubemap is that the cubemap
	is sampled using a direction vector instead of coordinates. That said, the cubemap
	vertices' position should always be in local space. */
	color = texture(material.cubemap_skybox, fs_in.texCoords);
}

END_FRAGMENT_SHADER
