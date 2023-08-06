#include "SpriteRendererComponent.h"

#include "../actor/Actor.h"

#include "TransformComponent.h"

SpriteRendererComponent::SpriteRendererComponent(Sprite* sprite)
	: sprite(sprite)
{
}

void SpriteRendererComponent::Render()
{
	if (parent && sprite)
	{
		TransformComponent* transformComponent = parent->FindComponentByType<TransformComponent>();
		if (transformComponent)
		{
			sprite->Render(transformComponent->GetModelTransformationMatrix());
		}
	}
}
