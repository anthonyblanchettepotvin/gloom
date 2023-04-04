#version 330 core

in vec2 passedTexCoords;

uniform sampler2D texture_sprite;

out vec4 color;

void main()
{
	color = texture(texture_sprite, passedTexCoords);
}
