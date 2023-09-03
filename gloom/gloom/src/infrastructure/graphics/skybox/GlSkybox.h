#pragma once

class Skybox;

class GlSkybox
{
public:
	GlSkybox(const Skybox& skybox);

	void Render();

private:
	void Initialize();

	const Skybox& m_Skybox;

	unsigned int m_Vao;
	unsigned int m_Vbo;
};
