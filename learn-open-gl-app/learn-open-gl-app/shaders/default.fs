#version 330 core

in vec2 passedTexCoords;

out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	color = mix(texture(texture1, passedTexCoords), texture(texture2, passedTexCoords), 0.2);
}
