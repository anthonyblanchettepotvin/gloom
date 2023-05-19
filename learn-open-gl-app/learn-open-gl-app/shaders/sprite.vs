#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

layout (std140) uniform ubo_matrices {
	mat4 view;
	mat4 skybox;
	mat4 projection;
};

uniform mat4 modelXform;

out VS_OUT {
	vec2 texCoords;
} vs_out;

void main()
{
	gl_Position = projection * view * modelXform * vec4(position, 1.0);

	vs_out.texCoords = texCoords;
}
