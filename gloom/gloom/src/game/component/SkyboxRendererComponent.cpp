#include "SkyboxRendererComponent.h"

#include "../../engine/graphics/scene/Scene.h"
#include "../../engine/graphics/skybox/Skybox.h"

SkyboxRendererComponent::SkyboxRendererComponent(Skybox* skybox)
	: m_Skybox(skybox)
{
}

void SkyboxRendererComponent::RegisterToScene(Scene& scene)
{
	if (!m_Skybox)
		return;

	scene.Register(*m_Skybox);
}

void SkyboxRendererComponent::UnregisterFromScene(Scene& scene)
{
	if (!m_Skybox)
		return;

	scene.Unregister(*m_Skybox);
}
