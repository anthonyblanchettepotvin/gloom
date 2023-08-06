#include "SpriteRendererComponent.h"

#include "../actor/Actor.h"

#include "TransformComponent.h"

SpriteRendererComponent::SpriteRendererComponent(GraphicsEngine& graphicsEngine, Sprite* sprite)
	: RendererComponent(graphicsEngine), m_Sprite(sprite)
{
}

void SpriteRendererComponent::Render()
{
	if (parent && m_Sprite)
	{
		TransformComponent* transformComponent = parent->FindComponentByType<TransformComponent>();
		if (transformComponent)
		{
			m_Sprite->Render(transformComponent->GetTransform());
		}
	}
}
