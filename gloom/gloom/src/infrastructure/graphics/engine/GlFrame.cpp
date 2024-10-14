#include "GlFrame.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>

#include "../../../engine/EngineGlobals.h"

#include "../texture/GlTexture.h"

#define FRAME_SHADER_PATH "..\\..\\assets\\shaders\\render.shader" // TODO: Move the shader in a OpenGL-specific folder.

std::string ImportFrameShaderCode()
{
	std::ifstream frameShaderFile;
	std::stringstream frameShaderFileBuf;

	try
	{
		frameShaderFile.open(FRAME_SHADER_PATH);
		frameShaderFileBuf << frameShaderFile.rdbuf();
		frameShaderFile.close();
	}
	catch (std::exception e)
	{
		std::stringstream ss;
		ss << "Could not import frame shader " << FRAME_SHADER_PATH << ".";
		gLogErrorMessageForKey("GlFrame", ss.str());

		return nullptr;
	}

	return frameShaderFileBuf.str();
}

GlFrame::GlFrame()
	: m_Shader(ImportFrameShaderCode()), m_GlShader(m_Shader)
{
}

void GlFrame::RenderTexture(GlTexture& texture)
{
	m_GlShader.Use();

	glBindVertexArray(m_Vao);
	texture.Use(0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	texture.Free();
	glBindVertexArray(0);

	m_GlShader.Free();
}

void GlFrame::Initialize()
{
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
