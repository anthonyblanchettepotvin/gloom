#pragma once

#include "RendererComponent.h"

class Sprite;

class SpriteRendererComponent : public RendererComponent
{
public:
	SpriteRendererComponent(Sprite* sprite);

	void RegisterToScene(Scene& scene) override;
	void UnregisterFromScene(Scene& scene) override;

	const Sprite* GetSprite() const { return m_Sprite; }

private:
	Sprite* m_Sprite = nullptr;
};
