#version 330 core

START_VERTEX_SHADER

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoords;

out VS_OUT{
    vec2 texCoords;
} vs_out;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);

    vs_out.texCoords = texCoords;
}

END_VERTEX_SHADER

START_FRAGMENT_SHADER

in VS_OUT{
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

END_FRAGMENT_SHADER
