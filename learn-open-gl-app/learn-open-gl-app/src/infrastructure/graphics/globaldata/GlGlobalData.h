#pragma once

#include <unordered_map>
#include <vector>

#include "../../../engine/graphics/globaldata/GlobalData.h"

#include "../globaldata/GlGlobalDataType.h"

class GlGlobalData : public GlobalData
{
public:
    GlGlobalData();

    void AddDataReference(const std::string& name, GlGlobalDataType& reference);

    void SendToDevice() override;

private:
    unsigned int id;
    unsigned int index;

    bool isAllocated = false;

    std::unordered_map<std::string, GlGlobalDataType*> references;
    std::vector<std::string> referencesNameOrdered;

    void Allocate();
    void Send();

    unsigned int GetUniformBufferSize() const;

    static unsigned int GetNextUniformBufferIndex();
};
