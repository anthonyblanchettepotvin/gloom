#version 330 core

layout (location = 0) in vec3 position;

layout (std140) uniform ubo_matrices {
	mat4 view;
	mat4 skybox;
	mat4 projection;
};

out VS_OUT {
    vec3 texCoords;
} vs_out;

void main()
{
    vec4 tempPosition = projection * skybox * vec4(position, 1.0);

    /* We set the gl_Position z value to the w value. When the perspective division is applied
    right after the vertex shader has run, the resulting z component will always be equal to 1.0,
    since w / w = 1.0, which is the maximum depth value. Remember that we want the skybox to be
    behind everything in the scene. */
    gl_Position = tempPosition.xyww;

    vs_out.texCoords = position;
}
