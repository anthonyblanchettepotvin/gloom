#include "Sprite.h"

Sprite::Sprite(Material* material)
	: m_Material(material)
{
}

void Sprite::Render(GraphicsEngine& graphicsEngine)
{
	graphicsEngine.RenderPrimitive(*this);
}
