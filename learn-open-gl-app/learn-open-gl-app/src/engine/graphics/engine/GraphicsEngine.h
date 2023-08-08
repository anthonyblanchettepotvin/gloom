#pragma once

#include "../../../game/asset/shader/ShaderLoader.h"

#include "../globaldata/GlobalData.h"
#include "../lighting/DirectionalLight.h"
#include "../lighting/PointLight.h"
#include "../rendering/Mesh.h"
#include "../rendering/Skybox.h"
#include "../rendering/Sprite.h"

class GraphicsEngine
{
public:
	virtual void Initialize(size_t width, size_t height) = 0;

	virtual void StartFrame() = 0;
	virtual void EndFrame() = 0;

	virtual std::unique_ptr<ShaderLoader> CreateShaderLoader() const = 0;

	virtual std::unique_ptr<GlobalData> CreateGlobalData(const std::string& name) const = 0;

	virtual void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, float& reference) = 0;
	virtual void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, glm::mat4& reference) = 0;
	virtual void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, glm::vec3& reference) = 0;
	virtual void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, DirectionalLight& reference) = 0;
	virtual void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, PointLight& reference) = 0;

	virtual void Render(const Mesh& mesh) = 0;
	virtual void Render(const Skybox& skybox) = 0;
	virtual void Render(const Sprite& sprite) = 0;
};
