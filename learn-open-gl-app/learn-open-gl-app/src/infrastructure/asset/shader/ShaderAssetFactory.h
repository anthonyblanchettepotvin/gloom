#pragma once

#include <memory>

#include "../../../engine/asset/AssetFactory.h"

class GraphicsEngine;

class ShaderAssetFactory : public AssetFactory
{
public:
	ShaderAssetFactory(GraphicsEngine& graphicsEngine);

protected:
	std::unique_ptr<ObjectBase> CreateBlankObject() override;

private:
	std::reference_wrapper<GraphicsEngine> m_GraphicsEngine;
};
