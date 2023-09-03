#include "SpriteRendererComponent.h"

#include "../../engine/graphics/engine/GraphicsEngine.h"
#include "../../engine/graphics/sprite/Sprite.h"

#include "../actor/Actor.h"

#include "TransformComponent.h"

SpriteRendererComponent::SpriteRendererComponent(GraphicsEngine& graphicsEngine, Sprite* sprite)
	: RendererComponent(graphicsEngine), m_Sprite(sprite)
{
}

void SpriteRendererComponent::Render()
{
	if (!m_Parent || !m_Sprite)
	{
		return;
	}

	TransformComponent* transformComponent = m_Parent->FindComponentByType<TransformComponent>();
	if (!transformComponent)
	{
		return;
	}

	m_Sprite->SetTransform(transformComponent->GetTransform());

	m_GraphicsEngine.Render(*m_Sprite);
}
