#include "Actor.h"

#include <iostream>

#include <glm/ext/matrix_transform.hpp>

#include "components/TransformComponent.h"
#include "components/RendererComponent.h"

Actor::Actor(const std::string& name)
	: name(name)
{
}

void Actor::Render()
{
	std::vector<RendererComponent*> rendererComponents = FindComponentsByType<RendererComponent>();
	for (auto rendererComponent : rendererComponents)
	{
		rendererComponent->Render();
	}
}

void Actor::AddComponent(ActorComponent* component)
{
	if (std::find(components.begin(), components.end(), component) == components.end())
	{
		components.push_back(component);

		component->SetParent(this);
	}
	else
	{
		std::cerr << "ERROR::ACTOR::ADD_COMPONENT::" << "Actor already has that component" << std::endl;
	}
}
