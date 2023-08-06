#pragma once

#include <vector>

#include "../../../../engine/graphics/rendering/GraphicsObject.h"
#include "../../../../engine/graphics/rendering/primitive/Mesh.h"

class GlMesh : public GraphicsObject
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
