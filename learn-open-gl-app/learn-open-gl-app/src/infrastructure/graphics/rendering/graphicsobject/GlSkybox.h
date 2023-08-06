#pragma once

#include "../../../../engine/graphics/rendering/GraphicsObject.h"
#include "../../../../engine/graphics/rendering/primitive/Skybox.h"

class GlSkybox : public GraphicsObject
{
public:
	GlSkybox(const Skybox& skybox);

	void Render();

private:
	const Skybox& m_Skybox;

	unsigned int m_Vao;
	unsigned int m_Vbo;

	void Initialize();
};
