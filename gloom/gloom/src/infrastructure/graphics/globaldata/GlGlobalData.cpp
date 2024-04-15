#include "GlGlobalData.h"

#include <cassert>
#include <stdexcept>

#include <glad/glad.h>

#include "../../../engine/EngineHelpers.h"

#include "GlGlobalDataType.h"

GlGlobalData::GlGlobalData(const std::string& name)
    : m_Name(name)
{
    m_Index = GetNextUniformBufferIndex();

    glGenBuffers(1, &m_Id);
    glBindBufferBase(GL_UNIFORM_BUFFER, m_Index, m_Id);
}

void GlGlobalData::SendToDevice()
{
    if (!m_IsAllocated)
    {
        Allocate();
    }

    glBindBuffer(GL_UNIFORM_BUFFER, m_Id);

    Send();

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void GlGlobalData::Allocate()
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
    glBufferData(GL_UNIFORM_BUFFER, GetUniformBufferSize(), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    m_IsAllocated = true;
}

unsigned int GlGlobalData::GetNextUniformBufferIndex()
{
    /* Here, choose an index for the UBO. So, if we want to bind the corresponding
    uniform block of a shader to this UBO, we'll need to bind it to the chosen index. */
    static unsigned int nextUniformBufferIndex = 0;

    return nextUniformBufferIndex++;
}
