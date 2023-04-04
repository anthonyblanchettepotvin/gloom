#pragma once

#include "../Sprite.h"

#include "RendererComponent.h"

class SpriteRendererComponent : public RendererComponent
{
public:
	SpriteRendererComponent(Sprite* sprite, Shader* shader);

	Sprite* GetSprite() { return sprite; };

	void Render() override;

private:
	Sprite* sprite;
};
