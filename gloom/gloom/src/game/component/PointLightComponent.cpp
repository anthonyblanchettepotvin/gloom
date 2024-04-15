#include "PointLightComponent.h"

#include "../../engine/EngineGlobals.h"
#include "../../engine/graphics/lighting/PointLight.h"

PointLightComponent::PointLightComponent(PointLight* pointLight)
    : m_PointLight(pointLight)
{
}

void PointLightComponent::OnParentSpawned()
{
    if (!m_PointLight)
        return;

    EngineGlobals::GetInstance().GetGraphicsEngine().RegisterLight(*m_PointLight);
}
