#pragma once

#include <memory>
#include <string>

class Camera;
class DirectionalLight;
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

	virtual void RegisterLight(DirectionalLight& directionalLight) = 0;
	virtual void RegisterLight(PointLight& pointLight) = 0;

	virtual void Render(const Camera&, Mesh& mesh) = 0;
	virtual void Render(const Camera&, Skybox& skybox) = 0;
	virtual void Render(const Camera&, Sprite& sprite) = 0;

	virtual void* GetTextureId(const Texture& texture) = 0;
};
