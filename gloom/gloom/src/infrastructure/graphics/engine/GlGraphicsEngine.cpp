#include "GlGraphicsEngine.h"

#include <glad/glad.h>

#include "../../../engine/EngineGlobals.h"
#include "../../../engine/graphics/camera/Camera.h"
#include "../../../engine/graphics/lighting/DirectionalLight.h"
#include "../../../engine/graphics/lighting/PointLight.h"
#include "../../../engine/graphics/material/Material.h"
#include "../../../engine/graphics/mesh/Mesh.h"
#include "../../../engine/graphics/sprite/Sprite.h"
#include "../../../engine/graphics/skybox/Skybox.h"
#include "../../../engine/graphics/texture/Texture.h"

#include "../mesh/GlMesh.h"
#include "../shader/GlShader.h"
#include "../skybox/GlSkybox.h"
#include "../sprite/GlSprite.h"

#include "GlFrame.h"
#include "GlFramebuffer.h"
#include "GlGraphicsData.h"
#include "GlRenderbufferAttachment.h"
#include "GlTextureAttachment.h"

void GlGraphicsEngine::Initialize(size_t width, size_t height)
{
	m_GraphicsData.Initialize(width, height);
}

void GlGraphicsEngine::StartFrame()
{
	// --- RENDERING PROCESS, STEP 1 ---
	/* During this step, we render the actual scene into our custom framebuffer. The result
	will be stored into the color attachment, which in our case is a texture. We will then
	use this texture during step 2 and render it on a quad that fits the screen perfectly. */
	m_GraphicsData.GetFramebuffer().Bind();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	/* We need to enable depth testing on each frame since the second render pass disable it
	to make sure the quad is rendered in front of everything else. */
	//if (settingsComponent.GetDepthTestingEnabledReference())
	glEnable(GL_DEPTH_TEST);
}

void GlGraphicsEngine::EndFrame()
{
	// --- RENDERING PROCESS, STEP 2 ---
	/* During this step, we render a quad that fits the screen perfectly using the texture that was
	generated during step 1. */
	m_GraphicsData.GetFramebuffer().Unbind();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	/* We need to disable depth testing to make sure the quad is rendered in front of everything else. */
	//if (settingsComponent.GetDepthTestingEnabledReference())
	glDisable(GL_DEPTH_TEST);

	m_GraphicsData.GetTextureAttachment().RenderToFrame(m_GraphicsData.GetFrame());
}

void GlGraphicsEngine::RegisterLight(DirectionalLight& directionalLight)
{
	m_GraphicsData.RegisterLight(directionalLight);
}

void GlGraphicsEngine::RegisterLight(PointLight& pointLight)
{
	m_GraphicsData.RegisterLight(pointLight);
}

void GlGraphicsEngine::Render(const Camera& camera, Mesh& mesh)
{
	if (!mesh.GetMaterial() || !mesh.GetMaterial() || !mesh.GetMaterial()->GetMaterialTemplate())
	{
		return;
	}

	const Material* material = mesh.GetMaterial();

	GlMesh& glMesh = m_GraphicsData.GetOrCreateMesh(mesh);
	GlShader& glShader = m_GraphicsData.GetOrCreateShader(material->GetMaterialTemplate()->GetShader());

	glShader.ApplyMaterial(*material, m_GraphicsData);
	glShader.SetFloatMat4("modelXform", mesh.GetTransform());
	glShader.BindToUniformBuffers(m_GraphicsData.GetUniformBufferRegistry());

	UpdateUniformBuffers(camera);
	SendUniformBuffersToDevice();

	glMesh.Render();

	m_GraphicsData.ResetSamplerIndex();
}

void GlGraphicsEngine::Render(const Camera& camera, Skybox& skybox)
{
	if (!skybox.GetMaterial() || !skybox.GetMaterial() || !skybox.GetMaterial()->GetMaterialTemplate())
	{
		return;
	}

	const Material* material = skybox.GetMaterial();

	GlSkybox& glSkybox = m_GraphicsData.GetOrCreateSkybox(skybox);
	GlShader& glShader = m_GraphicsData.GetOrCreateShader(material->GetMaterialTemplate()->GetShader());

	glShader.ApplyMaterial(*material, m_GraphicsData);
	glShader.BindToUniformBuffers(m_GraphicsData.GetUniformBufferRegistry());
	
	UpdateUniformBuffers(camera);
	SendUniformBuffersToDevice();

	glSkybox.Render();

	m_GraphicsData.ResetSamplerIndex();
}

void GlGraphicsEngine::Render(const Camera& camera, Sprite& sprite)
{
	if (!sprite.GetMaterial() || !sprite.GetMaterial() || !sprite.GetMaterial()->GetMaterialTemplate())
	{
		return;
	}

	const Material* material = sprite.GetMaterial();

	GlSprite& glSprite = m_GraphicsData.GetOrCreateSprite(sprite);
	GlShader& glShader = m_GraphicsData.GetOrCreateShader(material->GetMaterialTemplate()->GetShader());

	glShader.ApplyMaterial(*material, m_GraphicsData);
	glShader.SetFloatMat4("modelXform", sprite.GetTransform());
	glShader.BindToUniformBuffers(m_GraphicsData.GetUniformBufferRegistry());

	UpdateUniformBuffers(camera);
	SendUniformBuffersToDevice();

	glSprite.Render();

	m_GraphicsData.ResetSamplerIndex();
}

const MaterialTemplate* GlGraphicsEngine::GetMaterialTemplate(const Shader& shader)
{
	return &m_GraphicsData.GetOrCreateShader(shader).GetMaterialTemplate();
}

void* GlGraphicsEngine::GetTextureId(const Texture& texture)
{
	return (void*)m_GraphicsData.GetOrCreateTexture(texture).GetId();
}

void GlGraphicsEngine::UpdateUniformBuffers(const Camera& camera)
{
	m_GraphicsData.UpdateUniformBuffers(camera);
}

void GlGraphicsEngine::SendUniformBuffersToDevice()
{
	m_GraphicsData.SendUniformBuffersToDevice();
}
