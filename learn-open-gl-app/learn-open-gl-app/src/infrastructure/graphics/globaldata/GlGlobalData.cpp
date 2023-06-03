#include "GlGlobalData.h"

#include <glad/glad.h>
#include <iostream>

GlGlobalData::GlGlobalData()
{
    glGenBuffers(1, &id);

    index = GetNextUniformBufferIndex();
    glBindBufferBase(GL_UNIFORM_BUFFER, index, id);
}

void GlGlobalData::AddDataReference(const std::string& name, GlGlobalDataType& reference)
{
    references[name] = &reference;
    referencesNameOrdered.push_back(name);
}

void GlGlobalData::SendToDevice()
{
    if (!isAllocated)
    {
        Allocate();
    }

    Send();
}

void GlGlobalData::Allocate()
{
    glBindBuffer(GL_UNIFORM_BUFFER, id);
    glBufferData(GL_UNIFORM_BUFFER, GetUniformBufferSize(), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    isAllocated = true;
}

void GlGlobalData::Send()
{
    glBindBuffer(GL_UNIFORM_BUFFER, id);
    unsigned int offset = 0;
    for (const auto& referenceName : referencesNameOrdered)
    {
        GlGlobalDataType* currentReference = references.at(referenceName);

        // TODO: Put this function in a math library
        offset = currentReference->GetBaseAlignment() == 0 ? currentReference->GetBaseAlignment() : ceil(offset / currentReference->GetBaseAlignment()) * currentReference->GetBaseAlignment();

        glBufferSubData(GL_UNIFORM_BUFFER, offset, currentReference->GetSize(), currentReference->GetValuePointer());

        offset += currentReference->GetSize();
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

unsigned int GlGlobalData::GetUniformBufferSize() const
{
    unsigned int size = 0;
    for (const auto& referenceName : referencesNameOrdered)
    {
        GlGlobalDataType* currentReference = references.at(referenceName);

        // TODO: Put this function in a math library
        unsigned int offset = currentReference->GetBaseAlignment() == 0 ? currentReference->GetBaseAlignment() : ceil(size / currentReference->GetBaseAlignment()) * currentReference->GetBaseAlignment();

        size = offset + currentReference->GetSize();
    }
    return size;
}

unsigned int GlGlobalData::GetNextUniformBufferIndex()
{
    static unsigned int nextUniformBufferIndex = 0;

    return nextUniformBufferIndex++;
}
