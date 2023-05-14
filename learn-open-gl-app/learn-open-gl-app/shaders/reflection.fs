#version 330 core

struct Camera {
	vec3 position;
};

in vec3 passed_normal;
in vec3 passed_position;

uniform samplerCube cubemap_skybox;
uniform Camera camera;

out vec4 color;

void main()
{
	vec3 I = normalize(passed_position - camera.position);
	vec3 R = reflect(I, normalize(passed_normal));

	color = vec4(texture(cubemap_skybox, R).rgb, 1.0);
}
