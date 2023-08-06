#pragma once

#include "../../engine/graphics/texture/Sprite.h"

#include "RendererComponent.h"

class SpriteRendererComponent : public RendererComponent
{
public:
	SpriteRendererComponent(Sprite* sprite);

	Sprite* GetSprite() const { return m_Sprite; };

	void Render() override;

private:
	Sprite* m_Sprite;
};
