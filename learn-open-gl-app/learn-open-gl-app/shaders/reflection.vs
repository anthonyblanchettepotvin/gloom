#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

layout (std140) uniform ubo_matrices {
	mat4 view;
	mat4 skybox;
	mat4 projection;
};

uniform mat4 modelXform;
uniform mat3 normalXform;

out VS_OUT {
	vec3 position;
	vec3 normal;
} vs_out;

void main()
{
	gl_Position = projection * view * modelXform * vec4(position, 1.0);

	vs_out.position = vec3(modelXform * vec4(position, 1.0));
	vs_out.normal = normalXform * normal;
}
