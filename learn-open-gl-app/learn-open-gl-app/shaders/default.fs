#version 330 core

#define POINT_LIGHT_COUNT 4

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

in vec3 passedFragmentWorldPos;
in vec3 passedNormal;
in vec2 passedTexCoords;

out vec4 color;

uniform Material material;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[POINT_LIGHT_COUNT];
uniform Camera camera;

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragmentWorldPos, vec3 viewDirection);

void main()
{
	vec3 normNormal = normalize(passedNormal);
	vec3 viewDirection = normalize(camera.position - passedFragmentWorldPos);

	// Calculate directional lights contribution
	vec3 result = CalcDirectionalLight(directionalLight, normNormal, viewDirection);

	// Calculate point lights contribution
	for (int i = 0; i < POINT_LIGHT_COUNT; i++)
		result += max(CalcPointLight(pointLights[i], normNormal, passedFragmentWorldPos, viewDirection), 0.0);
	
	color = vec4(result, 1.0);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
	vec3 diffuseMapSample = vec3(texture(material.texture_diffuse1, passedTexCoords));
	vec3 specularMapSample = vec3(texture(material.texture_specular1, passedTexCoords));

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
	vec3 diffuseMapSample = vec3(texture(material.texture_diffuse1, passedTexCoords));
	vec3 specularMapSample = vec3(texture(material.texture_specular1, passedTexCoords));

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
