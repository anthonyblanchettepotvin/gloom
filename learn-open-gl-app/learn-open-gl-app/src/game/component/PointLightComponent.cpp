#include "PointLightComponent.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "../actor/Actor.h"

#include "TransformComponent.h"

void PointLightComponent::Register(Shader* shader, const std::string& identifier)
{
    if (shader && parent)
    {
        glm::vec3 position = glm::vec3(0.0f);
        TransformComponent* transformComponent = parent->FindComponentByType<TransformComponent>();
        if (transformComponent)
        {
            position = transformComponent->GetPositionReference();
        }

        shader->SetFloatVec3(identifier + ".position", position);

        shader->SetFloatVec3(identifier + ".ambientColor", ambientColor);
        shader->SetFloatVec3(identifier + ".diffuseColor", diffuseColor);
        shader->SetFloatVec3(identifier + ".specularColor", specularColor);

        shader->SetFloat(identifier + ".constant", attenuation.constant);
        shader->SetFloat(identifier + ".linear", attenuation.linear);
        shader->SetFloat(identifier + ".quadratic", attenuation.quadratic);
    }
}

void PointLightComponent::Register(unsigned int& offset)
{
    if (parent)
    {
        unsigned int localOffset = offset;

        glm::vec3 position = glm::vec3(0.0f);
        TransformComponent* transformComponent = parent->FindComponentByType<TransformComponent>();
        if (transformComponent)
        {
            position = transformComponent->GetPositionReference();
        }

        glBufferSubData(GL_UNIFORM_BUFFER, localOffset, sizeof(glm::vec3), glm::value_ptr(position));
        localOffset += sizeof(glm::vec4);

        glBufferSubData(GL_UNIFORM_BUFFER, localOffset, sizeof(glm::vec3), glm::value_ptr(ambientColor));
        localOffset += sizeof(glm::vec4);
        glBufferSubData(GL_UNIFORM_BUFFER, localOffset, sizeof(glm::vec3), glm::value_ptr(diffuseColor));
        localOffset += sizeof(glm::vec4);
        glBufferSubData(GL_UNIFORM_BUFFER, localOffset, sizeof(glm::vec3), glm::value_ptr(specularColor));
        localOffset += sizeof(glm::vec4);

        glBufferSubData(GL_UNIFORM_BUFFER, localOffset, sizeof(int), &attenuation.constant);
        localOffset += sizeof(int);
        glBufferSubData(GL_UNIFORM_BUFFER, localOffset, sizeof(int), &attenuation.linear);
        localOffset += sizeof(int);
        glBufferSubData(GL_UNIFORM_BUFFER, localOffset, sizeof(int), &attenuation.quadratic);
        localOffset += sizeof(int);

        offset += 80;
    }
}
