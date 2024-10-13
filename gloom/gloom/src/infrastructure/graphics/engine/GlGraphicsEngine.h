#pragma once

#include <unordered_map>
#include <vector>

#include "../../../engine/graphics/engine/GraphicsEngine.h"

#include "GlGraphicsData.h"

class Camera;
class CubemapMaterialAttribute;
class DirectionalLight;
class FloatMaterialAttribute;
class GlShader;
class Material;
class MaterialAttribute;
class PointLight;
class TextureMaterialAttribute;

class GlGraphicsEngine : public GraphicsEngine
{
public:
	void Initialize(size_t width, size_t height) override;

	void StartFrame() override;
	void EndFrame() override;

	std::unique_ptr<Shader> CreateShader() override;
	std::unique_ptr<Shader> ImportShader(const std::string& filePath) override;

	void RegisterLight(DirectionalLight& directionalLight) override;
	void RegisterLight(PointLight& pointLight) override;

	void Render(const Camera&, Mesh& mesh) override;
	void Render(const Camera&, Skybox& skybox) override;
	void Render(const Camera&, Sprite& sprite) override;
	
	void* GetTextureId(const Texture& texture) override;

private:
	void UpdateUniformBuffers(const Camera& camera);
	void SendUniformBuffersToDevice();

	void ApplyMaterial(Material& material);
	void ApplyMaterialAttributeToShader(GlShader& shader, const MaterialAttribute* attribute);
	void ApplyMaterialAttributeToShader(GlShader& shader, const CubemapMaterialAttribute& attribute);
	void ApplyMaterialAttributeToShader(GlShader& shader, const FloatMaterialAttribute& attribute);
	void ApplyMaterialAttributeToShader(GlShader& shader, const TextureMaterialAttribute& attribute);

	GlGraphicsData m_GraphicsData;

	size_t m_SamplerIndex = 0;
};
