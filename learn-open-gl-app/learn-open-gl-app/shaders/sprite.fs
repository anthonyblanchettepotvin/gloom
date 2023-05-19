#version 330 core

in VS_OUT {
	vec2 texCoords;
} fs_in;

uniform sampler2D texture_sprite;

out vec4 color;

void main()
{
	color = texture(texture_sprite, fs_in.texCoords);
}
