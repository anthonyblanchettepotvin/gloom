#version 330 core

struct Camera {
	vec3 position;
};

in VS_OUT {
    vec3 position;
	vec3 normal;
} fs_in;

uniform samplerCube cubemap_skybox;

layout (std140) uniform ubo_camera {
	Camera camera;
};

out vec4 color;

void main()
{
	/* We passed from air to glass, so we take the refractive index of air over
	the refractive index of water. */
	// See https://learnopengl.com/Advanced-OpenGL/Cubemaps for more details on refraction.
	float ratio = 1.0 / 1.52;

	vec3 I = normalize(fs_in.position - camera.position);
	vec3 R = refract(I, normalize(fs_in.normal), ratio);

	color = vec4(texture(cubemap_skybox, R).rgb, 1.0);
}
