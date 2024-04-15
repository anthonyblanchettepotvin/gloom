#pragma once

#include <string>

#include "../../../engine/graphics/globaldata/GlobalData.h"

class GlGlobalData : public GlobalData
{
public:
    GlGlobalData(const std::string& name);

    void SendToDevice() override;

    std::string GetName() const { return m_Name; }

    unsigned int GetIndex() const { return m_Index; }

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
