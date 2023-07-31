#pragma once

#include "../../../engine/graphics/engine/GraphicsEngine.h"

class GlGraphicsEngine : public GraphicsEngine
{
public:
	GlobalData* CreateGlobalData(const std::string& name) override;

	void AddDataReferenceToGlobalData(const std::string& name, float& reference, GlobalData* globalData) override;
	void AddDataReferenceToGlobalData(const std::string& name, glm::mat4& reference, GlobalData* globalData) override;
	void AddDataReferenceToGlobalData(const std::string& name, glm::vec3& reference, GlobalData* globalData) override;
	void AddDataReferenceToGlobalData(const std::string& name, DirectionalLight& reference, GlobalData* globalData) override;
	void AddDataReferenceToGlobalData(const std::string& name, PointLight& reference, GlobalData* globalData) override;
};
