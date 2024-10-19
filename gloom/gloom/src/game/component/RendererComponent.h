#pragma once

#include "ActorComponent.h"

class Scene;

class RendererComponent : public ActorComponent
{
public:
	void OnParentSpawned() override;
	void OnParentDespawned() override;

	virtual void RegisterToScene(Scene& scene) = 0;
	virtual void UnregisterFromScene(Scene& scene) = 0;
};
