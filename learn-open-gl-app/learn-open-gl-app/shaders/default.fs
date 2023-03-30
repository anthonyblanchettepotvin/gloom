#version 330 core

struct Material {
	sampler2D diffuseMap;
	sampler2D specularMap;
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
	vec3 diffuseMapSample = vec3(texture(material.diffuseMap, passedTexCoords));
	vec3 specularMapSample = vec3(texture(material.specularMap, passedTexCoords));

	// Ambient
	vec3 ambient = light.ambientColor * diffuseMapSample;

	// Diffuse
	vec3 normNormal = normalize(passedNormal);
	vec3 normLightDirection = normalize(light.position - passedFragmentWorldPos);
	
	float diffuseStrength = max(dot(normNormal, normLightDirection), 0.0);
	vec3 diffuse = light.diffuseColor * diffuseMapSample * diffuseStrength;

	// Specular
	vec3 viewDirection = normalize(camera.position - passedFragmentWorldPos);
	vec3 reflectDirection = reflect(-normLightDirection, normNormal);

	float specularStrength = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = light.specularColor * specularMapSample * specularStrength;

	// Output
	color = vec4(ambient + diffuse + specular, 1.0);
}
