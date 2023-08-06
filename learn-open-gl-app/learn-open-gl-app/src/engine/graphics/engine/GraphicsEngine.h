#pragma once

#include "../../../game/asset/shader/ShaderLoader.h"

#include "../globaldata/GlobalData.h"
#include "../lighting/DirectionalLight.h"
#include "../lighting/PointLight.h"
#include "../rendering/primitive/Mesh.h"
#include "../rendering/primitive/Skybox.h"
#include "../rendering/primitive/Sprite.h"
#include "../rendering/GraphicsObject.h"

class GraphicsEngine
{
public:
	virtual void Initialize(size_t width, size_t height) = 0;

	virtual void StartFrame() = 0;
	virtual void EndFrame() = 0;

	virtual ShaderLoader& GetShaderLoader() = 0;

	virtual GlobalData* CreateGlobalData(const std::string& name) = 0;

	virtual void AddDataReferenceToGlobalData(const std::string& name, float& reference, GlobalData* globalData) = 0;
	virtual void AddDataReferenceToGlobalData(const std::string& name, glm::mat4& reference, GlobalData* globalData) = 0;
	virtual void AddDataReferenceToGlobalData(const std::string& name, glm::vec3& reference, GlobalData* globalData) = 0;
	virtual void AddDataReferenceToGlobalData(const std::string& name, DirectionalLight& reference, GlobalData* globalData) = 0;
	virtual void AddDataReferenceToGlobalData(const std::string& name, PointLight& reference, GlobalData* globalData) = 0;

	virtual GraphicsObject* CreateGraphicsObject(const Mesh& mesh) = 0;
	virtual GraphicsObject* CreateGraphicsObject(const Skybox& skybox) = 0;
	virtual GraphicsObject* CreateGraphicsObject(const Sprite& sprite) = 0;
};
