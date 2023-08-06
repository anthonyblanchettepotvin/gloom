#version 330 core

START_VERTEX_SHADER

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(std140) uniform ubo_matrices{
	mat4 view;
	mat4 skybox;
	mat4 projection;
};

uniform mat4 modelXform;

out VS_OUT{
	vec3 position;
	vec3 normal;
} vs_out;

void main()
{
	gl_Position = projection * view * modelXform * vec4(position, 1.0);

	mat3 normalXform = transpose(inverse(mat3(modelXform)));

	vs_out.position = vec3(modelXform * vec4(position, 1.0));
	vs_out.normal = normalXform * normal;
}

END_VERTEX_SHADER

START_FRAGMENT_SHADER

struct Camera {
	vec3 position;
};

in VS_OUT{
	vec3 position;
	vec3 normal;
} fs_in;

uniform samplerCube cubemap_skybox;

layout(std140) uniform ubo_camera{
	Camera camera;
};

out vec4 color;

void main()
{
	// See https://learnopengl.com/Advanced-OpenGL/Cubemaps for more details on reflection.
	vec3 I = normalize(fs_in.position - camera.position);
	vec3 R = reflect(I, normalize(fs_in.normal));

	color = vec4(texture(cubemap_skybox, R).rgb, 1.0);
}

END_FRAGMENT_SHADER
