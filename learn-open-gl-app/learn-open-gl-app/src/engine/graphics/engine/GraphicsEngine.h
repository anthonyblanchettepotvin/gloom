#pragma once

#include "../globaldata/GlobalData.h"

class GraphicsEngine
{
public:
	virtual GlobalData* CreateGlobalData() = 0;

	virtual void AddDataReferenceToGlobalData(const std::string& name, glm::mat4& reference, GlobalData* globalData) = 0;
};
