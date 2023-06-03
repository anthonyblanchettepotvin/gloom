#pragma once

#include "../../../engine/graphics/engine/GraphicsEngine.h"

class GlGraphicsEngine : public GraphicsEngine
{
public:
	GlobalData* CreateGlobalData() override;

	void AddDataReferenceToGlobalData(const std::string& name, glm::mat4& reference, GlobalData* globalData) override;
};
