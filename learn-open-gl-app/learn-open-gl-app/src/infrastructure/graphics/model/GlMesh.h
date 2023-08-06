#pragma once

#include <vector>

#include "../../../engine/graphics/model/Mesh.h"
#include "../../../engine/graphics/rendering/GraphicsObject.h"

class GlMesh : public GraphicsObject
{
public:
	GlMesh(const Mesh& mesh);

	void Render() override;

private:
	const Mesh& m_Mesh;

	unsigned int m_Vao;
	unsigned int m_Vbo;
	unsigned int m_Ebo;

	void Initialize();
};
