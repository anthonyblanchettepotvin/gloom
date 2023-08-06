#include "GlSprite.h"

#include <glad/glad.h>

#include "../../../game/asset/shader/Shader.h"

GlSprite::GlSprite(const Sprite& sprite)
    : m_Sprite(sprite)
{
    Initialize();
}

void GlSprite::Render()
{
    Material* material = m_Sprite.GetMaterial();
    if (material)
    {
        material->Use();

        material->GetShader().SetFloatMat4("modelXform", m_Sprite.GetTransform());

        glBindVertexArray(m_Vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}

void GlSprite::Initialize()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
    };

    glGenVertexArrays(1, &m_Vao);
    glBindVertexArray(m_Vao);

    glGenBuffers(1, &m_Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
