#pragma once

#include "../../engine/graphics/rendering/Sprite.h"

#include "RendererComponent.h"

class SpriteRendererComponent : public RendererComponent
{
public:
	SpriteRendererComponent(GraphicsEngine& graphicsEngine, Sprite* sprite);

	Sprite* GetSprite() const { return m_Sprite; };

	void Render() override;

private:
	Sprite* m_Sprite;
};
