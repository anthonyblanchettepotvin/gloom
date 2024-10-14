#pragma once

#include <unordered_map>
#include <vector>

#include "../../../engine/graphics/engine/GraphicsEngine.h"

#include "GlGraphicsData.h"

class Camera;
class DirectionalLight;
class GlShader;
class Material;
class MaterialAttributeBase;
class PointLight;

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

	void ApplyMaterial(GlShader& shader, const Material& material);
	void ApplyMaterialAttribute(GlShader& shader, const MaterialAttributeBase* attribute);
	// TODO: The following methods could be templated and we could use template specialization for the Cubemap* and Texture* cases.
	void ApplyMaterialAttribute(GlShader& shader, const MaterialAttribute<Cubemap*>& attribute);
	void ApplyMaterialAttribute(GlShader& shader, const MaterialAttribute<float>& attribute);
	void ApplyMaterialAttribute(GlShader& shader, const MaterialAttribute<Texture*>& attribute);

	GlGraphicsData m_GraphicsData;

	size_t m_SamplerIndex = 0;
};
