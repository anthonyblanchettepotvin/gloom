#include "DirectionalLightComponent.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

void DirectionalLightComponent::Register(Shader* shader, const std::string& identifier)
{
    if (shader)
    {
        shader->SetFloatVec3(identifier + ".direction", direction);

        shader->SetFloatVec3(identifier + ".ambientColor", ambientColor);
        shader->SetFloatVec3(identifier + ".diffuseColor", diffuseColor);
        shader->SetFloatVec3(identifier + ".specularColor", specularColor);
    }
}

void DirectionalLightComponent::Register(unsigned int& offset)
{
    unsigned int localOffset = offset;

    glBufferSubData(GL_UNIFORM_BUFFER, localOffset, sizeof(glm::vec3), glm::value_ptr(direction));
    localOffset += sizeof(glm::vec4);

    glBufferSubData(GL_UNIFORM_BUFFER, localOffset, sizeof(glm::vec3), glm::value_ptr(ambientColor));
    localOffset += sizeof(glm::vec4);
    glBufferSubData(GL_UNIFORM_BUFFER, localOffset, sizeof(glm::vec3), glm::value_ptr(diffuseColor));
    localOffset += sizeof(glm::vec4);
    glBufferSubData(GL_UNIFORM_BUFFER, localOffset, sizeof(glm::vec3), glm::value_ptr(specularColor));
    localOffset += sizeof(glm::vec4);

    offset += 64;
}
