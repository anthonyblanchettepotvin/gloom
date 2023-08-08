#pragma once

#include "../../../engine/graphics/rendering/Mesh.h"

class GlMesh
{
public:
	GlMesh(const Mesh& mesh);

	void Render();

private:
	const Mesh& m_Mesh;

	unsigned int m_Vao;
	unsigned int m_Vbo;
	unsigned int m_Ebo;

	void Initialize();
};
