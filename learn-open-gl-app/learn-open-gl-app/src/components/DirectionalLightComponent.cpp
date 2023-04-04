#include "DirectionalLightComponent.h"

void DirectionalLightComponent::Register(Shader* shader, const std::string& identifier)
{
    if (shader)
    {
        shader->setFloatVec3(identifier + ".direction", direction);
        shader->setFloatVec3(identifier + ".ambientColor", ambientColor);
        shader->setFloatVec3(identifier + ".diffuseColor", diffuseColor);
        shader->setFloatVec3(identifier + ".specularColor", specularColor);
    }
}
