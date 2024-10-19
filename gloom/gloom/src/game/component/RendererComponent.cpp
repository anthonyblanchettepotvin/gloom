#include "RendererComponent.h"

#include "../actor/Actor.h"
#include "../world/World.h"

void RendererComponent::OnParentSpawned()
{
	if (!m_Parent)
		return;

	World* world = m_Parent->GetWorld();
	if (!world)
		return;

	RegisterToScene(world->GetScene());
}

void RendererComponent::OnParentDespawned()
{
	if (!m_Parent)
		return;

	World* world = m_Parent->GetWorld();
	if (!world)
		return;

	UnregisterFromScene(world->GetScene());
}
