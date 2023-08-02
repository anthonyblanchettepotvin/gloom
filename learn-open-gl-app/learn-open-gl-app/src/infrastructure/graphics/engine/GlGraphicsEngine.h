#pragma once

#include "../../../engine/graphics/engine/GraphicsEngine.h"

#include "../model/GlModelLoader.h"
#include "../shader/GlShader.h"
#include "../shader/GlShaderLoader.h"
#include "../texture/GlCubemapLoader.h"
#include "../texture/GlTexture.h"
#include "../texture/GlTextureLoader.h"

#include "GlFramebuffer.h"
#include "GlRenderbuffer.h"
#include "GlRenderSurface.h"

class GlGraphicsEngine : public GraphicsEngine
{
public:
	GlGraphicsEngine();

	void Initialize(size_t width, size_t height) override;
	
	void StartFrame() override;
	void EndFrame() override;

	CubemapLoader& GetCubemapLoader() override { return m_CubemapLoader; }
	ModelLoader& GetModelLoader() override { return m_ModelLoader; }
	ShaderLoader& GetShaderLoader() override { return m_ShaderLoader; };
	TextureLoader& GetTextureLoader() override { return m_TextureLoader; };

	GlobalData* CreateGlobalData(const std::string& name) override;

	void AddDataReferenceToGlobalData(const std::string& name, float& reference, GlobalData* globalData) override;
	void AddDataReferenceToGlobalData(const std::string& name, glm::mat4& reference, GlobalData* globalData) override;
	void AddDataReferenceToGlobalData(const std::string& name, glm::vec3& reference, GlobalData* globalData) override;
	void AddDataReferenceToGlobalData(const std::string& name, DirectionalLight& reference, GlobalData* globalData) override;
	void AddDataReferenceToGlobalData(const std::string& name, PointLight& reference, GlobalData* globalData) override;

private:
	GlCubemapLoader m_CubemapLoader;
	GlModelLoader m_ModelLoader;
	GlShaderLoader m_ShaderLoader;
	GlTextureLoader m_TextureLoader;

	GlFramebuffer* m_Framebuffer = nullptr;
	GlTexture* m_RenderTexture = nullptr;
	GlRenderbuffer* m_Renderbuffer = nullptr;
	GlShader* m_RenderShader = nullptr;
	GlRenderSurface* m_RenderSurface = nullptr;
};
