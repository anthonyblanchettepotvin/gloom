#pragma once

#include "../globaldata/GlobalData.h"
#include "../lighting/DirectionalLight.h"
#include "../lighting/PointLight.h"

class GraphicsEngine
{
public:
	virtual GlobalData* CreateGlobalData(const std::string& name) = 0;

	virtual void AddDataReferenceToGlobalData(const std::string& name, float& reference, GlobalData* globalData) = 0;
	virtual void AddDataReferenceToGlobalData(const std::string& name, glm::mat4& reference, GlobalData* globalData) = 0;
	virtual void AddDataReferenceToGlobalData(const std::string& name, glm::vec3& reference, GlobalData* globalData) = 0;
	virtual void AddDataReferenceToGlobalData(const std::string& name, DirectionalLight& reference, GlobalData* globalData) = 0;
	virtual void AddDataReferenceToGlobalData(const std::string& name, PointLight& reference, GlobalData* globalData) = 0;
};
