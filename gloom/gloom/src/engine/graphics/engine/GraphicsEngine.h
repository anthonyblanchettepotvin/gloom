#pragma once

class Camera;
class MaterialTemplate;
class Scene;
class Shader;
class Texture;

class GraphicsEngine
{
public:
	virtual void Initialize(size_t width, size_t height) = 0;

	virtual void RenderScene(const Scene& scene, const Camera& camera) = 0;

	virtual const MaterialTemplate* GetMaterialTemplate(const Shader& shader) = 0;

	virtual void* GetTextureId(const Texture& texture) = 0;
};
