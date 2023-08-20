#version 330 core

START_VERTEX_SHADER

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

layout(std140) uniform ubo_matrices{
	mat4 view;
	mat4 skybox;
	mat4 projection;
};

uniform mat4 modelXform;

out VS_OUT{
	vec3 fragmentWorldPos;
	vec3 normal;
	vec2 texCoords;
} vs_out;

void main()
{
	gl_Position = projection * view * modelXform * vec4(position, 1.0);

	/* Here, we create our normal transformation matrix. Since our normals are hard-coded
	data within the vertices data, we need to transform the normals if we apply a scaling or rotation
	transformation on the cube. */
	/* Note that we don't care about the translation, since normals are directions. That's why we
	convert the 4x4 matrix into a 3x3 matrix -- to remove the translation. */
	/* Note that if we apply a non-uniform scaling transformation, the normals may not be
	perpendicular to the surface anymore. We then inverse then transpose the model matrix
	that our normal transformation matrix is based on. */
	/* See https://learnopengl.com/Lighting/Basic-Lighting for more details. */
	mat3 normalXform = transpose(inverse(mat3(modelXform)));

	vs_out.fragmentWorldPos = vec3(modelXform * vec4(position, 1.0));
	vs_out.normal = normalXform * normal;
	vs_out.texCoords = texCoords;
}

END_VERTEX_SHADER

START_FRAGMENT_SHADER

#define DIRECTIONAL_LIGHT_COUNT 1
#define POINT_LIGHT_COUNT 1

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_specular3;
	float shininess;
};

struct PointLight {
	vec3 position;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;

	float constant;
	float linear;
	float quadratic;
};

struct DirectionalLight {
	vec3 direction;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

struct Camera {
	vec3 position;
};

in VS_OUT{
	vec3 fragmentWorldPos;
	vec3 normal;
	vec2 texCoords;
} fs_in;

uniform Material material;

layout(std140) uniform ubo_directionalLights{
	DirectionalLight directionalLights[DIRECTIONAL_LIGHT_COUNT];
};

layout(std140) uniform ubo_pointLights{
	PointLight pointLights[POINT_LIGHT_COUNT];
};

layout(std140) uniform ubo_camera{
	Camera camera;
};

out vec4 color;

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragmentWorldPos, vec3 viewDirection);

void main()
{
	vec3 normNormal = normalize(fs_in.normal);
	vec3 viewDirection = normalize(camera.position - fs_in.fragmentWorldPos);

	vec3 result;

	// Calculate directional lights contribution
	for (int i = 0; i < DIRECTIONAL_LIGHT_COUNT; i++)
		result += max(CalcDirectionalLight(directionalLights[i], normNormal, viewDirection), 0.0);

	// Calculate point lights contribution
	for (int i = 0; i < POINT_LIGHT_COUNT; i++)
		result += max(CalcPointLight(pointLights[i], normNormal, fs_in.fragmentWorldPos, viewDirection), 0.0);

	color = vec4(result, 1.0);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
	vec3 diffuseMapSample = vec3(texture(material.texture_diffuse1, fs_in.texCoords));
	vec3 specularMapSample = vec3(texture(material.texture_specular1, fs_in.texCoords));

	// Ambient
	vec3 ambient = light.ambientColor * diffuseMapSample;

	// Diffuse
	vec3 normLightDirection = normalize(light.direction);

	float diffuseStrength = max(dot(normal, -normLightDirection), 0.0);
	vec3 diffuse = light.diffuseColor * diffuseMapSample * diffuseStrength;

	// Specular
	vec3 reflectDirection = reflect(normLightDirection, normal);

	float specularStrength = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = light.specularColor * specularMapSample * specularStrength;

	// Output
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragmentWorldPos, vec3 viewDirection) {
	vec3 diffuseMapSample = vec3(texture(material.texture_diffuse1, fs_in.texCoords));
	vec3 specularMapSample = vec3(texture(material.texture_specular1, fs_in.texCoords));

	// Ambient
	vec3 ambient = light.ambientColor * diffuseMapSample;

	// Diffuse
	vec3 normLightDirection = normalize(fragmentWorldPos - light.position);

	float diffuseStrength = max(dot(normal, -normLightDirection), 0.0);
	vec3 diffuse = light.diffuseColor * diffuseMapSample * diffuseStrength;

	// Specular
	vec3 reflectDirection = reflect(normLightDirection, normal);

	float specularStrength = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = light.specularColor * specularMapSample * specularStrength;

	// Attenuation
	float distance = length(fragmentWorldPos - light.position);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	// Output
	return (ambient + diffuse + specular);
}

END_FRAGMENT_SHADER
