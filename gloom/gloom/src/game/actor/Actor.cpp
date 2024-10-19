#include "Actor.h"

#include <iostream>

#include <glm/ext/matrix_transform.hpp>

#include "../../engine/EngineHelpers.h"

#include "../component/ActorComponent.h"
#include "../world/World.h"

#define COMPONENT_ALREADY_ADDED_TO_ACTOR "Component is already added to the actor."

Actor::Actor(const std::string& name)
	: m_Name(name)
{
}

void Actor::OnSpawned(World& world)
{
	m_World = &world;

	for (const auto& component : m_Components)
	{
		assert(component != nullptr);

		component->OnParentSpawned();
	}
}

void Actor::OnDespawned()
{
	for (const auto& component : m_Components)
	{
		assert(component != nullptr);

		component->OnParentDespawned();
	}

	m_World = nullptr;
}

void Actor::AddComponent(std::unique_ptr<ActorComponent>& component)
{
	if (!component)
	{
		throw std::invalid_argument(ARGUMENT_IS_NULLPTR(component));
	}

	auto it = std::find(m_Components.begin(), m_Components.end(), component);
	if (it != m_Components.end())
	{
		throw std::runtime_error(COMPONENT_ALREADY_ADDED_TO_ACTOR);
	}

	component->SetParent(this);

	m_Components.emplace_back(std::move(component));
}

std::vector<ActorComponent*> Actor::GetComponents()
{
	std::vector<ActorComponent*> result;

	for (const auto& component : m_Components)
	{
		assert(component != nullptr);

		result.emplace_back(component.get());
	}

	return result;
}
