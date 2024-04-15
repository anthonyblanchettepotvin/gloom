#pragma once

#include <memory>
#include <string>

class Mesh;
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

	virtual void Render(Mesh& mesh) = 0;
	virtual void Render(Skybox& skybox) = 0;
	virtual void Render(Sprite& sprite) = 0;

	virtual void* GetTextureId(const Texture& texture) = 0;
};
