#version 330 core

in vec2 passedTexCoords;

uniform sampler2D texture_screen;

out vec4 color;

void main()
{ 
    float red_offset = 0;
    float green_offset = 0.001;
    float blue_offset = -0.001;

    color.r = texture(texture_screen, passedTexCoords + red_offset).r;
    color.g = texture(texture_screen, passedTexCoords + green_offset).g;
    color.b = texture(texture_screen, passedTexCoords + blue_offset).b;
    color.a = 1.0;
}
