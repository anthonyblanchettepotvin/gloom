#pragma once

#include <unordered_map>
#include <vector>

#include "../../../engine/graphics/engine/GraphicsEngine.h"
#include "../../../engine/object/ObjectID.h"

class Camera;
class CubemapMaterialAttribute;
class DirectionalLight;
class FloatMaterialAttribute;
class GlCameraUniformBuffer;
class GlCubemap;
class GlDirectionalLightsUniformBuffer;
class GlFrame;
class GlFramebuffer;
class GlMatricesUniformBuffer;
class GlMesh;
class GlPointLightsUniformBuffer;
class GlRenderbufferAttachment;
class GlShader;
class GlSkybox;
class GlSprite;
class GlTexture;
class GlTextureAttachment;
class Material;
class MaterialAttribute;
class PointLight;
class TextureMaterialAttribute;

class GlGraphicsEngine : public GraphicsEngine
{
public:
	GlGraphicsEngine();
	~GlGraphicsEngine();

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
	void InitializeGlobalData();
	void BindShaderToUniformBuffers(GlShader& shader);
	void UpdateGlobalData(const Camera& camera);

	void ApplyMaterial(Material& material);
	void ApplyMaterialAttributeToShader(GlShader& shader, const MaterialAttribute* attribute);
	void ApplyMaterialAttributeToShader(GlShader& shader, const CubemapMaterialAttribute& attribute);
	void ApplyMaterialAttributeToShader(GlShader& shader, const FloatMaterialAttribute& attribute);
	void ApplyMaterialAttributeToShader(GlShader& shader, const TextureMaterialAttribute& attribute);

	std::unique_ptr<GlFrame> m_Frame = nullptr;
	std::unique_ptr<GlFramebuffer> m_Framebuffer = nullptr;
	std::unique_ptr<GlRenderbufferAttachment> m_RenderbufferAttachment = nullptr;
	std::unique_ptr<GlTextureAttachment> m_TextureAttachment = nullptr;

	std::unique_ptr<GlMatricesUniformBuffer> m_MatricesUniformBuffer = nullptr;
	std::unique_ptr<GlDirectionalLightsUniformBuffer> m_DirectionalLightsUniformBuffer = nullptr;
	std::unique_ptr<GlPointLightsUniformBuffer> m_PointLightsUniformBuffer = nullptr;
	std::unique_ptr<GlCameraUniformBuffer> m_CameraUniformBuffer = nullptr;

	std::vector<DirectionalLight*> m_DirectionalLights;
	std::vector<PointLight*> m_PointLights;

	std::unordered_map<ObjectID, std::unique_ptr<GlCubemap>> m_GlCubemaps;
	std::unordered_map<ObjectID, std::unique_ptr<GlMesh>> m_GlMeshes;
	std::unordered_map<ObjectID, std::unique_ptr<GlSkybox>> m_GlSkyboxes;
	std::unordered_map<ObjectID, std::unique_ptr<GlSprite>> m_GlSprites;
	std::unordered_map<ObjectID, std::unique_ptr<GlTexture>> m_GlTextures;

	size_t m_SamplerIndex = 0;
};
