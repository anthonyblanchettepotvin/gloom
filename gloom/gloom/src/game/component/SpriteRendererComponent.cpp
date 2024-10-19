#include "SpriteRendererComponent.h"

#include "../../engine/graphics/scene/Scene.h"
#include "../../engine/graphics/sprite/Sprite.h"

#include "../actor/Actor.h"

#include "TransformComponent.h"

SpriteRendererComponent::SpriteRendererComponent(Sprite* sprite)
	: m_Sprite(sprite)
{
}

void SpriteRendererComponent::RegisterToScene(Scene& scene)
{
	if (!m_Parent || !m_Sprite)
		return;

	TransformComponent* transformComponent = m_Parent->FindComponentByType<TransformComponent>();
	if (!transformComponent)
		return;

	m_Sprite->SetTransform(transformComponent->GetTransform());

	scene.Register(*m_Sprite);
}

void SpriteRendererComponent::UnregisterFromScene(Scene& scene)
{
	if (!m_Sprite)
		return;

	scene.Unregister(*m_Sprite);
}
