#include "DirectionalLightComponent.h"

#include "../../engine/graphics/lighting/DirectionalLight.h"
#include "../../engine/graphics/scene/Scene.h"

DirectionalLightComponent::DirectionalLightComponent(DirectionalLight* directionalLight)
    : m_DirectionalLight(directionalLight)
{
}

void DirectionalLightComponent::RegisterToScene(Scene& scene)
{
    if (!m_DirectionalLight)
        return;

    scene.Register(*m_DirectionalLight);
}

void DirectionalLightComponent::UnregisterFromScene(Scene& scene)
{
    if (!m_DirectionalLight)
        return;

    scene.Unregister(*m_DirectionalLight);
}
