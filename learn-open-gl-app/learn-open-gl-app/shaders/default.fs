#version 330 core

struct Material {
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float shininess;
};

struct Light {
	vec3 position;

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
uniform Light light;
uniform Camera camera;

void main()
{
	// Ambient
	vec3 ambient = light.ambientColor * material.ambientColor;

	// Diffuse
	vec3 normNormal = normalize(passedNormal);
	vec3 normLightDirection = normalize(light.position - passedFragmentWorldPos);
	
	float diffuseStrength = max(dot(normNormal, normLightDirection), 0.0);
	vec3 diffuse = light.diffuseColor * material.diffuseColor * diffuseStrength;

	// Specular
	vec3 viewDirection = normalize(camera.position - passedFragmentWorldPos);
	vec3 reflectDirection = reflect(-normLightDirection, normNormal);

	float specularStrength = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = light.specularColor * material.specularColor * specularStrength;

	// Output
	color = vec4(ambient + diffuse + specular, 1.0);
}
