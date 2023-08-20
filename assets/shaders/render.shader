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
    color = texture(texture_screen, fs_in.texCoords);
}

END_FRAGMENT_SHADER
