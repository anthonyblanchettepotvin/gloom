#pragma once

#include <memory>

#include "../../../engine/asset/AssetFactory.h"

class GraphicsEngine;

class ShaderAssetFactory : public AssetFactory
{
public:
	ShaderAssetFactory(GraphicsEngine& graphicsEngine);

protected:
	std::unique_ptr<Object> CreateBlankObject() override;

private:
	GraphicsEngine& m_GraphicsEngine;
};
