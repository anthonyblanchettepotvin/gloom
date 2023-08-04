#pragma once

#include "../globaldata/GlobalData.h"
#include "../lighting/DirectionalLight.h"
#include "../lighting/PointLight.h"
#include "../shader/ShaderLoader.h"
#include "../texture/CubemapLoader.h"
#include "../../../game/asset/model/ModelLoader.h"
#include "../../../game/asset/texture/TextureLoader.h"

class GraphicsEngine
{
public:
	virtual void Initialize(size_t width, size_t height) = 0;

	virtual void StartFrame() = 0;
	virtual void EndFrame() = 0;

	virtual CubemapLoader& GetCubemapLoader() = 0;
	virtual ModelLoader& GetModelLoader() = 0;
	virtual ShaderLoader& GetShaderLoader() = 0;
	virtual TextureLoader& GetTextureLoader() = 0;

	virtual GlobalData* CreateGlobalData(const std::string& name) = 0;

	virtual void AddDataReferenceToGlobalData(const std::string& name, float& reference, GlobalData* globalData) = 0;
	virtual void AddDataReferenceToGlobalData(const std::string& name, glm::mat4& reference, GlobalData* globalData) = 0;
	virtual void AddDataReferenceToGlobalData(const std::string& name, glm::vec3& reference, GlobalData* globalData) = 0;
	virtual void AddDataReferenceToGlobalData(const std::string& name, DirectionalLight& reference, GlobalData* globalData) = 0;
	virtual void AddDataReferenceToGlobalData(const std::string& name, PointLight& reference, GlobalData* globalData) = 0;
};
