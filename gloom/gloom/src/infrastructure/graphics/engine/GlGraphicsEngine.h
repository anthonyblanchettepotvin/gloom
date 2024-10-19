#pragma once

#include <unordered_map>
#include <vector>
#include <chrono>

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

	void RenderScene(const Scene& scene, const Camera& camera) override;

	const MaterialTemplate* GetMaterialTemplate(const Shader& shader) override;
	
	void* GetTextureId(const Texture& texture) override;

private:
	void StartFrame(const Camera& camera);
	void EndFrame();

	void RegisterLight(const DirectionalLight& directionalLight);
	void RegisterLight(const PointLight& pointLight);

	void Render(const Mesh& mesh, const Camera& camera);
	void Render(const Skybox& skybox, const Camera& camera);
	void Render(const Sprite& sprite, const Camera& camera);

	void UpdateUniformBuffers(const Camera& camera);
	void SendUniformBuffersToDevice();

	GlGraphicsData m_GraphicsData;

	std::chrono::system_clock::time_point m_FrameStartTime;
	std::chrono::system_clock::time_point m_FrameEndTime;
	std::chrono::milliseconds m_FrameDuration;
};
