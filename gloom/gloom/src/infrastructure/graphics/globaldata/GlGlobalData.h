#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../../engine/graphics/globaldata/GlobalData.h"

class GlGlobalDataType;

class GlGlobalData : public GlobalData
{
public:
    GlGlobalData(const std::string& name);

    void SendToDevice() override;

    void AddDataReference(const std::string& name, std::unique_ptr<GlGlobalDataType>& reference);

    std::string GetName() const { return m_Name; }

    unsigned int GetIndex() const { return m_Index; }

private:
    void Allocate();
    void Send();

    unsigned int GetUniformBufferSize() const;

    static unsigned int GetNextUniformBufferIndex();

    std::string m_Name;

    unsigned int m_Id;
    unsigned int m_Index;

    bool m_IsAllocated = false;

    std::unordered_map<std::string, std::unique_ptr<GlGlobalDataType>> m_References;
    std::vector<std::string> m_ReferencesNameOrdered;
};
