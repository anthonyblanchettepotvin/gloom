#include "PointLightComponent.h"

#include "../../engine/graphics/lighting/PointLight.h"
#include "../../engine/graphics/scene/Scene.h"

PointLightComponent::PointLightComponent(PointLight* pointLight)
    : m_PointLight(pointLight)
{
}

void PointLightComponent::RegisterToScene(Scene& scene)
{
    if (!m_PointLight)
        return;

    scene.Register(*m_PointLight);
}

void PointLightComponent::UnregisterFromScene(Scene& scene)
{
    if (!m_PointLight)
        return;

    scene.Unregister(*m_PointLight);
}
