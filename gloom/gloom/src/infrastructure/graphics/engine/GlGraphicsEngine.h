#pragma once

#include <unordered_map>

#include "../../../engine/graphics/engine/GraphicsEngine.h"
#include "../../../engine/object/ObjectID.h"

class Material;
class MaterialAttribute;
class CubemapMaterialAttribute;
class FloatMaterialAttribute;
class GlCubemap;
class GlFrame;
class GlFramebuffer;
class GlMesh;
class GlRenderbufferAttachment;
class GlShader;
class GlSkybox;
class GlSprite;
class GlTexture;
class GlTextureAttachment;
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

	std::unique_ptr<GlobalData> CreateGlobalData(const std::string& name) override;

	void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, float& reference) override;
	void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, glm::mat4& reference) override;
	void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, glm::vec3& reference) override;
	void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, DirectionalLight& reference) override;
	void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, PointLight& reference) override;

	void Render(Mesh& mesh) override;
	void Render(Skybox& skybox) override;
	void Render(Sprite& sprite) override;
	
	void* GetTextureId(const Texture& texture) override;

private:
	void ApplyMaterial(Material& material);
	void ApplyMaterialAttributeToShader(GlShader& shader, const MaterialAttribute* attribute);
	void ApplyMaterialAttributeToShader(GlShader& shader, const CubemapMaterialAttribute& attribute);
	void ApplyMaterialAttributeToShader(GlShader& shader, const FloatMaterialAttribute& attribute);
	void ApplyMaterialAttributeToShader(GlShader& shader, const TextureMaterialAttribute& attribute);

	std::unique_ptr<GlFrame> m_Frame = nullptr;
	std::unique_ptr<GlFramebuffer> m_Framebuffer = nullptr;
	std::unique_ptr<GlRenderbufferAttachment> m_RenderbufferAttachment = nullptr;
	std::unique_ptr<GlTextureAttachment> m_TextureAttachment = nullptr;

	std::unordered_map<ObjectID, std::unique_ptr<GlCubemap>> m_GlCubemaps;
	std::unordered_map<ObjectID, std::unique_ptr<GlMesh>> m_GlMeshes;
	std::unordered_map<ObjectID, std::unique_ptr<GlSkybox>> m_GlSkyboxes;
	std::unordered_map<ObjectID, std::unique_ptr<GlSprite>> m_GlSprites;
	std::unordered_map<ObjectID, std::unique_ptr<GlTexture>> m_GlTextures;

	size_t m_SamplerIndex = 0;
};
