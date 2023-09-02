#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

class DirectionalLight;
class GlobalData;
class Material;
class Mesh;
class PointLight;
class Shader;
class Skybox;
class Sprite;
class Texture;

class GraphicsEngine
{
public:
	virtual void Initialize(size_t width, size_t height) = 0;

	virtual void StartFrame() = 0;
	virtual void EndFrame() = 0;

	virtual std::unique_ptr<Shader> CreateShader() = 0;
	virtual std::unique_ptr<Shader> ImportShader(const std::string& filePath) = 0;

	virtual GlobalData* CreateGlobalData(const std::string& name) const = 0;

	virtual void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, float& reference) = 0;
	virtual void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, glm::mat4& reference) = 0;
	virtual void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, glm::vec3& reference) = 0;
	virtual void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, DirectionalLight& reference) = 0;
	virtual void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, PointLight& reference) = 0;

	virtual void Render(Mesh& mesh) = 0;
	virtual void Render(Skybox& skybox) = 0;
	virtual void Render(Sprite& sprite) = 0;

	virtual void* GetTextureId(const Texture& texture) = 0;
};
