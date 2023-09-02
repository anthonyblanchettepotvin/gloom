#pragma once

#include "RendererComponent.h"

class Sprite;

class SpriteRendererComponent : public RendererComponent
{
public:
	SpriteRendererComponent(GraphicsEngine& graphicsEngine, Sprite* sprite);

	void Render() override;

	const Sprite* GetSprite() const { return m_Sprite; }

private:
	Sprite* m_Sprite = nullptr;
};
