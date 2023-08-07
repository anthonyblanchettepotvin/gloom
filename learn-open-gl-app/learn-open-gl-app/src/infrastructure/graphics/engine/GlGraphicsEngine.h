#pragma once

#include <unordered_map>

#include "../../../engine/graphics/engine/GraphicsEngine.h"
#include "../../../engine/graphics/material/Material.h"
#include "../../../engine/graphics/material/MaterialAttribute.h"
#include "../../../engine/graphics/material/MaterialAttributes.h"

#include "../shader/GlShader.h"
#include "../shader/GlShaderLoader.h"
#include "../rendering/GlCubemap.h"
#include "../rendering/GlMesh.h"
#include "../rendering/GlSkybox.h"
#include "../rendering/GlSprite.h"
#include "../rendering/GlTexture.h"

#include "GlFramebuffer.h"
#include "GlRenderbuffer.h"
#include "GlRenderSurface.h"

class GlGraphicsEngine : public GraphicsEngine
{
public:
	void Initialize(size_t width, size_t height) override;
	
	void StartFrame() override;
	void EndFrame() override;

	ShaderLoader& GetShaderLoader() override { return m_ShaderLoader; };

	GlobalData* CreateGlobalData(const std::string& name) override;

	void AddDataReferenceToGlobalData(const std::string& name, float& reference, GlobalData* globalData) override;
	void AddDataReferenceToGlobalData(const std::string& name, glm::mat4& reference, GlobalData* globalData) override;
	void AddDataReferenceToGlobalData(const std::string& name, glm::vec3& reference, GlobalData* globalData) override;
	void AddDataReferenceToGlobalData(const std::string& name, DirectionalLight& reference, GlobalData* globalData) override;
	void AddDataReferenceToGlobalData(const std::string& name, PointLight& reference, GlobalData* globalData) override;

	void Render(const Mesh& mesh) override;
	void Render(const Skybox& skybox) override;
	void Render(const Sprite& sprite) override;

private:
	GlShaderLoader m_ShaderLoader;

	GlFramebuffer* m_Framebuffer = nullptr;
	GlTexture* m_RenderTexture = nullptr;
	GlRenderbuffer* m_Renderbuffer = nullptr;
	GlShader* m_RenderShader = nullptr;
	GlRenderSurface* m_RenderSurface = nullptr;

	std::unordered_map<const Mesh*, GlMesh*> m_GlMeshes;
	std::unordered_map<const Skybox*, GlSkybox*> m_GlSkyboxes;
	std::unordered_map<const Sprite*, GlSprite*> m_GlSprites;
	std::unordered_map<const Texture*, GlTexture*> m_GlTextures;
	std::unordered_map<const Cubemap*, GlCubemap*> m_GlCubemaps;

	size_t m_SamplerIndex = 0;

	void ApplyMaterial(Material* attribute);
	void ApplyMaterialAttributeToShader(MaterialAttribute* attribute, Shader& shader);
	void ApplyTextureAttributeToShader(TextureMaterialAttribute* attribute, Shader& shader);
	void ApplyCubemapAttributeToShader(CubemapMaterialAttribute* attribute, Shader& shader);
	void ApplyFloatAttributeToShader(FloatMaterialAttribute* attribute, Shader& shader);
};
