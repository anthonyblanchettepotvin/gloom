#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

layout (std140) uniform ubo_matrices {
	mat4 view;
	mat4 skybox;
	mat4 projection;
};

uniform mat4 modelXform;
uniform mat3 normalXform;

out VS_OUT {
	vec3 fragmentWorldPos;
	vec3 normal;
	vec2 texCoords;
} vs_out;

void main()
{
	gl_Position = projection * view * modelXform * vec4(position, 1.0);

	vs_out.fragmentWorldPos = vec3(modelXform * vec4(position, 1.0));
	vs_out.normal = normalXform * normal;
	vs_out.texCoords = texCoords;
}
