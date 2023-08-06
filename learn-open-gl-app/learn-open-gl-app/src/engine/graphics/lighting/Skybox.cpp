#include "Skybox.h"

Skybox::Skybox(Material* material)
	: m_Material(material)
{
}

void Skybox::Render(GraphicsEngine& graphicsEngine)
{
	graphicsEngine.RenderPrimitive(*this);
}
