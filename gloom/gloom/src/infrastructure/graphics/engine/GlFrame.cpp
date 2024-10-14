#include "GlFrame.h"

#include <stdexcept>

#include <glad/glad.h>

#include "../../../engine/EngineHelpers.h"

#include "../shader/GlShader.h"
#include "../texture/GlTexture.h"

void GlFrame::RenderTexture(GlTexture& texture)
{
	m_Shader->Use();

	glBindVertexArray(m_Vao);
	texture.Use(0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	texture.Free();
	glBindVertexArray(0);

	m_Shader->Free();
}

void GlFrame::Initialize(std::unique_ptr<GlShader>& shader)
{
	if (!shader)
	{
		throw std::invalid_argument(ARGUMENT_IS_NULLPTR(shader));
	}

	m_Shader = std::move(shader);

	float vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
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
