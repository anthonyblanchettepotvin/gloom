#pragma once

class Camera;
class DirectionalLight;
class MaterialTemplate;
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

	virtual void RegisterLight(DirectionalLight& directionalLight) = 0;
	virtual void RegisterLight(PointLight& pointLight) = 0;

	virtual void Render(const Camera&, Mesh& mesh) = 0;
	virtual void Render(const Camera&, Skybox& skybox) = 0;
	virtual void Render(const Camera&, Sprite& sprite) = 0;

	virtual const MaterialTemplate* GetMaterialTemplate(const Shader& shader) = 0;

	virtual void* GetTextureId(const Texture& texture) = 0;
};
