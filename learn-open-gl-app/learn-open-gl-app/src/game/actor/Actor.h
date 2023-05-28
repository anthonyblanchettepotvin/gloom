#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "../../engine/graphics/shader/Shader.h"

class ActorComponent;

class Actor
{
public:
	Actor(const std::string& name);

	std::string GetName() { return name; }

	std::vector<ActorComponent*> GetComponents() { return components; }

	void AddComponent(ActorComponent* component);

	template<typename T>
	std::vector<T*> FindComponentsByType() const;

	template<typename T>
	T* FindComponentByType() const;

	void Render();

private:
	std::string name;

	std::vector<ActorComponent*> components;
};

template<typename T>
inline std::vector<T*> Actor::FindComponentsByType() const
{
	std::vector<T*> componentsOfType;

	for (auto component : components)
	{
		if (T* castedComponent = dynamic_cast<T*>(component))
		{
			componentsOfType.push_back(castedComponent);
		}
	}

	return componentsOfType;
}

template<typename T>
T* Actor::FindComponentByType() const
{
	for (auto component : components)
	{
		if (T* castedComponent = dynamic_cast<T*>(component))
		{
			return castedComponent;
		}
	}

	return nullptr;
}
