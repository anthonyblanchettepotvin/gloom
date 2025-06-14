#version 400 core

START_VERTEX_SHADER

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;

layout(std140) uniform ubo_matrices{
	mat4 view;
	mat4 skybox;
	mat4 projection;
};

uniform mat4 modelXform;

out VS_OUT{
	vec3 fragmentWorldPos;
	vec2 texCoords;
} vs_out;

void main()
{
	gl_Position = projection * view * modelXform * vec4(position, 1.0);

	vs_out.fragmentWorldPos = vec3(modelXform * vec4(position, 1.0));
	vs_out.texCoords = texCoords;
}

END_VERTEX_SHADER

START_FRAGMENT_SHADER

struct Material {
	sampler2D texture_sprite;
};

in VS_OUT{
	vec3 fragmentWorldPos;
	vec2 texCoords;
} fs_in;

uniform Material material;

layout (location = 0) out vec4 accum;
layout (location = 1) out float reveal;

void main()
{
	vec4 color = texture(material.texture_sprite, fs_in.texCoords);

	float weight = max(min(1.0, max(max(color.r, color.g), color.b) * color.a), color.a) * clamp(0.03 / (1e-5 + pow(fs_in.fragmentWorldPos.z / 200, 4.0)), 1e-2, 3e3);

	accum = vec4(color.rgb * color.a, color.a) * weight;
	reveal = color.a;
}

END_FRAGMENT_SHADER
