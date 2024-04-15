#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "../../engine/object/Object.h"

class ActorComponent;
class Camera;

class Actor : public Object
{
public:
	Actor(const std::string& name);

	void OnSpawned();

	void Render(const Camera& camera);

	void AddComponent(std::unique_ptr<ActorComponent>& component);

	template<typename T>
	std::vector<T*> FindComponentsByType();

	template<typename T>
	T* FindComponentByType();

	std::string GetName() const { return m_Name; }

	std::vector<ActorComponent*> GetComponents();

private:
	std::string m_Name;

	std::vector<std::unique_ptr<ActorComponent>> m_Components;
};

template<typename T>
inline std::vector<T*> Actor::FindComponentsByType()
{
	std::vector<T*> result;

	for (const auto& component : m_Components)
	{
		if (T* castedComponent = dynamic_cast<T*>(component.get()))
		{
			result.emplace_back(castedComponent);
		}
	}

	return result;
}

template<typename T>
inline T* Actor::FindComponentByType()
{
	for (const auto& component : m_Components)
	{
		if (T* castedComponent = dynamic_cast<T*>(component.get()))
		{
			return castedComponent;
		}
	}

	return nullptr;
}
