#include "SpriteRendererComponent.h"

#include "../Actor.h"

#include "TransformComponent.h"

SpriteRendererComponent::SpriteRendererComponent(Sprite* sprite, Shader* shader)
	: RendererComponent(shader), sprite(sprite)
{
}

void SpriteRendererComponent::Render()
{
	if (parent && shader && sprite)
	{
		TransformComponent* transformComponent = parent->FindComponentByType<TransformComponent>();
		if (transformComponent)
		{
			shader->setFloatMat4("modelXform", transformComponent->GetModelTransformationMatrix());

			sprite->Render(shader);
		}
	}
}
