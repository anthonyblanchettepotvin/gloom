#pragma once

#include "../../engine/graphics/texture/Sprite.h"

#include "RendererComponent.h"

class SpriteRendererComponent : public RendererComponent
{
public:
	SpriteRendererComponent(Sprite* sprite);

	Sprite* GetSprite() { return sprite; };

	void Render() override;

private:
	Sprite* sprite;
};
