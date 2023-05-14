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
	/* We passed from air to glass, so we take the refractive index of air over
	the refractive index of water. */
	// See https://learnopengl.com/Advanced-OpenGL/Cubemaps for more details on refraction.
	float ratio = 1.0 / 1.52;

	vec3 I = normalize(passed_position - camera.position);
	vec3 R = refract(I, normalize(passed_normal), ratio);

	color = vec4(texture(cubemap_skybox, R).rgb, 1.0);
}
