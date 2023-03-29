#version 330 core

in vec3 passedFragmentWorldPos;
in vec3 passedNormal;
in vec2 passedTexCoords;

out vec4 color;

uniform sampler2D texture1;
uniform vec3 lightColor1;
uniform vec3 lightPosition1;
uniform vec3 cameraPosition;

void main()
{
	vec3 normNormal = normalize(passedNormal);
	vec3 normLightDirection = normalize(lightPosition1 - passedFragmentWorldPos);

	vec4 objectColor = texture(texture1, passedTexCoords);

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor1;

	float diffuseStrength = max(dot(normNormal, normLightDirection), 0.0);
	vec3 diffuse = diffuseStrength * lightColor1;

	float specularStrength = 1.0;
	vec3 viewDirection = normalize(cameraPosition - passedFragmentWorldPos);
	vec3 reflectDirection = reflect(-normLightDirection, normNormal);

	float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0), 8);
	vec3 specular = specularStrength * specularIntensity * lightColor1;

	color = vec4(ambient + diffuse + specular, 1.0) * objectColor;
}
