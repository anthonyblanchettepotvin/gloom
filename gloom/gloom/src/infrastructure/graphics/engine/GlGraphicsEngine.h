#pragma once

#include <unordered_map>
#include <vector>

#include "../../../engine/graphics/engine/GraphicsEngine.h"

#include "GlGraphicsData.h"

class Camera;
class DirectionalLight;
class Mesh;
class PointLight;
class Skybox;
class Shader;
class Sprite;
class Texture;

class GlGraphicsEngine : public GraphicsEngine
{
public:
	void Initialize(size_t width, size_t height) override;

	void StartFrame() override;
	void EndFrame() override;

	void RegisterLight(DirectionalLight& directionalLight) override;
	void RegisterLight(PointLight& pointLight) override;

	void Render(const Camera&, Mesh& mesh) override;
	void Render(const Camera&, Skybox& skybox) override;
	void Render(const Camera&, Sprite& sprite) override;

	const MaterialTemplate* GetMaterialTemplate(const Shader& shader) override;
	
	void* GetTextureId(const Texture& texture) override;

private:
	void UpdateUniformBuffers(const Camera& camera);
	void SendUniformBuffersToDevice();

	GlGraphicsData m_GraphicsData;
};
