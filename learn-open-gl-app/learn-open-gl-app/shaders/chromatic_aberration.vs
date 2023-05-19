#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out VS_OUT {
    vec2 texCoords;
} vs_out;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0, 1.0); 

    vs_out.texCoords = texCoords;
}
