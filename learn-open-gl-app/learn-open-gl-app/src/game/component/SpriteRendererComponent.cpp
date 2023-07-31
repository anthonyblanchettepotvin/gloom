#include "SpriteRendererComponent.h"

#include "../actor/Actor.h"

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
			shader->Use();

			shader->SetFloatMat4("modelXform", transformComponent->GetModelTransformationMatrix());

			sprite->Render(shader);
		}
	}
}
