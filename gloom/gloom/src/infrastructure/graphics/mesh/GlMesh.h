#pragma once

class Mesh;

class GlMesh
{
public:
	GlMesh(const Mesh& mesh);

	void Render();

private:
	void Initialize();

	const Mesh& m_Mesh;

	unsigned int m_Vao;
	unsigned int m_Vbo;
	unsigned int m_Ebo;
};
