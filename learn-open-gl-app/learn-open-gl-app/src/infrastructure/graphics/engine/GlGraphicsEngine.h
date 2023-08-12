#pragma once

#include <unordered_map>

#include "../../../engine/object/ObjectID.h"
#include "../../../engine/graphics/engine/GraphicsEngine.h"
#include "../../../engine/graphics/material/Material.h"
#include "../../../engine/graphics/material/MaterialAttribute.h"
#include "../../../engine/graphics/material/MaterialAttributes.h"

#include "../cubemap/GlCubemap.h"
#include "../mesh/GlMesh.h"
#include "../shader/GlShader.h"
#include "../shader/GlShaderImporter.h"
#include "../skybox/GlSkybox.h"
#include "../sprite/GlSprite.h"
#include "../texture/GlTexture.h"

#include "GlFramebuffer.h"
#include "GlRenderbuffer.h"
#include "GlRenderSurface.h"

class GlGraphicsEngine : public GraphicsEngine
{
public:
	void Initialize(size_t width, size_t height) override;
	
	void StartFrame() override;
	void EndFrame() override;

	ShaderImporter* CreateShaderImporter() const override;

	GlobalData* CreateGlobalData(const std::string& name) const override;

	void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, float& reference) override;
	void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, glm::mat4& reference) override;
	void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, glm::vec3& reference) override;
	void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, DirectionalLight& reference) override;
	void AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, PointLight& reference) override;

	void Render(const Mesh& mesh) override;
	void Render(const Skybox& skybox) override;
	void Render(const Sprite& sprite) override;

private:
	std::unique_ptr<GlFramebuffer> m_Framebuffer = nullptr;
	std::unique_ptr<GlTexture> m_RenderTexture = nullptr;
	std::unique_ptr<GlRenderbuffer> m_Renderbuffer = nullptr;
	std::unique_ptr<GlShader> m_RenderShader = nullptr;
	std::unique_ptr<GlRenderSurface> m_RenderSurface = nullptr;

	std::unordered_map<ObjectID, std::unique_ptr<GlMesh>> m_GlMeshes;
	std::unordered_map<ObjectID, std::unique_ptr<GlSkybox>> m_GlSkyboxes;
	std::unordered_map<ObjectID, std::unique_ptr<GlSprite>> m_GlSprites;
	std::unordered_map<ObjectID, std::unique_ptr<GlTexture>> m_GlTextures;
	std::unordered_map<ObjectID, std::unique_ptr<GlCubemap>> m_GlCubemaps;

	size_t m_SamplerIndex = 0;

	void ApplyMaterial(const Material& material);
	void ApplyMaterialAttributeToShader(Shader& shader, MaterialAttribute* attribute);
	void ApplyMaterialAttributeToShader(Shader& shader, TextureMaterialAttribute* attribute);
	void ApplyMaterialAttributeToShader(Shader& shader, CubemapMaterialAttribute* attribute);
	void ApplyMaterialAttributeToShader(Shader& shader, FloatMaterialAttribute* attribute);
};
