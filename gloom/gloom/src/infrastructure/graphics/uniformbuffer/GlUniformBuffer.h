#pragma once

#include <string>

class Camera;
class GlGraphicsData;

class GlUniformBuffer
{
public:
    GlUniformBuffer(const std::string& name);

    void SendToDevice();

    std::string GetName() const { return m_Name; }

    unsigned int GetIndex() const { return m_Index; }

    virtual void Update(const Camera& camera, const GlGraphicsData& graphicsData) = 0; // TODO: Move Camera in GlGraphicsData?

protected:
    virtual void Send() = 0;

    virtual unsigned int GetUniformBufferSize() const = 0;

private:
    void Allocate();

    static unsigned int GetNextUniformBufferIndex();

    std::string m_Name;

    unsigned int m_Id;
    unsigned int m_Index;

    bool m_IsAllocated = false;
};
