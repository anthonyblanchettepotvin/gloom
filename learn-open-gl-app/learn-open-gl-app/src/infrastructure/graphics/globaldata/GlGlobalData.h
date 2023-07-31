#pragma once

#include <unordered_map>
#include <vector>

#include "../../../engine/graphics/globaldata/GlobalData.h"

#include "../globaldata/GlGlobalDataType.h"

class GlGlobalData : public GlobalData
{
public:
    GlGlobalData(const std::string& name);

    std::string GetName() { return m_Name; }

    unsigned int GetIndex() { return m_Index; }

    void AddDataReference(const std::string& name, GlGlobalDataType& reference);

    void SendToDevice() override;

private:
    std::string m_Name;

    unsigned int m_Id;
    unsigned int m_Index;

    bool m_IsAllocated = false;

    std::unordered_map<std::string, GlGlobalDataType*> m_References;
    std::vector<std::string> m_ReferencesNameOrdered;

    void Allocate();
    void Send();

    unsigned int GetUniformBufferSize() const;

    static unsigned int GetNextUniformBufferIndex();
};
