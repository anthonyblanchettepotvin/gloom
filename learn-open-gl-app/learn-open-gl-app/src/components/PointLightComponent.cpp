#include "PointLightComponent.h"

#include "../Actor.h"

#include "TransformComponent.h"

void PointLightComponent::Register(Shader* shader, const std::string& identifier)
{
    if (shader && parent)
    {
        TransformComponent* transformComponent = parent->FindComponentByType<TransformComponent>();
        if (transformComponent)
        {
            shader->setFloatVec3(identifier + ".position", transformComponent->GetPositionReference());
        }
        else
        {
            shader->setFloatVec3(identifier + ".position", glm::vec3(0.0f));
        }

        shader->setFloatVec3(identifier + ".ambientColor", ambientColor);
        shader->setFloatVec3(identifier + ".diffuseColor", diffuseColor);
        shader->setFloatVec3(identifier + ".specularColor", specularColor);
        shader->setFloat(identifier + ".constant", attenuation.constant);
        shader->setFloat(identifier + ".linear", attenuation.linear);
        shader->setFloat(identifier + ".quadratic", attenuation.quadratic);
    }
}
