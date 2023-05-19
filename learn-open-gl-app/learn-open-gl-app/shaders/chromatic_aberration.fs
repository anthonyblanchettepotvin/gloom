#version 330 core

in VS_OUT {
    vec2 texCoords;
} fs_in;

uniform sampler2D texture_screen;

out vec4 color;

void main()
{ 
    float red_offset = 0;
    float green_offset = 0.001;
    float blue_offset = -0.001;

    color.r = texture(texture_screen, fs_in.texCoords + red_offset).r;
    color.g = texture(texture_screen, fs_in.texCoords + green_offset).g;
    color.b = texture(texture_screen, fs_in.texCoords + blue_offset).b;
    color.a = 1.0;
}
