#include "DirectionalLightComponent.h"

#include "../../engine/EngineGlobals.h"
#include "../../engine/graphics/lighting/DirectionalLight.h"

DirectionalLightComponent::DirectionalLightComponent(DirectionalLight* directionalLight)
    : m_DirectionalLight(directionalLight)
{
}

void DirectionalLightComponent::OnParentSpawned()
{
    if (!m_DirectionalLight)
        return;

    EngineGlobals::GetInstance().GetGraphicsEngine().RegisterLight(*m_DirectionalLight);
}
