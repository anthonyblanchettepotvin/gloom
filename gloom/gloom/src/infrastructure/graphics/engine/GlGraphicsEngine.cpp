#include "GlGraphicsEngine.h"

#include <glad/glad.h>

#include "../../../engine/EngineGlobals.h"
#include "../../../engine/graphics/camera/Camera.h"
#include "../../../engine/graphics/lighting/DirectionalLight.h"
#include "../../../engine/graphics/lighting/PointLight.h"
#include "../../../engine/graphics/material/Material.h"
#include "../../../engine/graphics/mesh/Mesh.h"
#include "../../../engine/graphics/scene/Scene.h"
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

void GlGraphicsEngine::RenderScene(const Scene& scene, const Camera& camera)
{
	// Register the lights before the uniform buffers are updated.
	for (const auto& directionalLight : scene.GetDirectionalLights())
	{
		if (directionalLight == nullptr) // TODO: Hate having to null-check here.
			continue;

		RegisterLight(*directionalLight);
	}

	for (const auto& pointLight : scene.GetPointLights())
	{
		if (pointLight == nullptr) // TODO: Hate having to null-check here.
			continue;

		RegisterLight(*pointLight);
	}

	StartFrame(camera);

	// TODO: Visit the scene and render in the correct order (i.e., render transparent objects first, from furthest to closest).

	for (const auto& mesh : scene.GetMeshes())
	{
		if (mesh == nullptr) // TODO: Hate having to null-check here.
			continue;

		Render(*mesh, camera);
	}

	for (const auto& sprite : scene.GetSprites())
	{
		if (sprite == nullptr) // TODO: Hate having to null-check here.
			continue;

		Render(*sprite, camera);
	}

	for (const auto& skybox : scene.GetSkyboxes())
	{
		if (skybox == nullptr) // TODO: Hate having to null-check here.
			continue;

		Render(*skybox, camera);
	}

	EndFrame();
}

void GlGraphicsEngine::StartFrame(const Camera& camera)
{
	m_FrameStartTime = std::chrono::system_clock::now();

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

	m_GraphicsData.UpdateUniformBuffers(camera);
	m_GraphicsData.SendUniformBuffersToDevice();
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

	m_FrameEndTime = std::chrono::system_clock::now();
	m_FrameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(m_FrameEndTime - m_FrameStartTime);

	gLogInfoMessage(std::to_string(m_FrameDuration.count()));
}

void GlGraphicsEngine::RegisterLight(const DirectionalLight& directionalLight)
{
	m_GraphicsData.RegisterLight(directionalLight);
}

void GlGraphicsEngine::RegisterLight(const PointLight& pointLight)
{
	m_GraphicsData.RegisterLight(pointLight);
}

void GlGraphicsEngine::Render(const Mesh& mesh, const Camera& camera)
{
	const Material* material = mesh.GetMaterial();
	if (!material)
		return; // TODO: LogWarning

	const MaterialTemplate* materialTemplate = material->GetMaterialTemplate();
	if (!materialTemplate)
		return; // TODO: LogWarning

	GlMesh& glMesh = m_GraphicsData.GetOrCreateMesh(mesh);
	GlShader& glShader = m_GraphicsData.GetOrCreateShader(material->GetMaterialTemplate()->GetShader());

	glShader.ApplyMaterial(*material, m_GraphicsData);
	glShader.SetFloatMat4("modelXform", mesh.GetTransform());
	glShader.BindToUniformBuffers(m_GraphicsData.GetUniformBufferRegistry());

	glMesh.Render();

	m_GraphicsData.ResetSamplerIndex();
}

void GlGraphicsEngine::Render(const Skybox& skybox, const Camera& camera)
{
	const Material* material = skybox.GetMaterial();
	if (!material)
		return; // TODO: LogWarning

	const MaterialTemplate* materialTemplate = material->GetMaterialTemplate();
	if (!materialTemplate)
		return; // TODO: LogWarning

	GlSkybox& glSkybox = m_GraphicsData.GetOrCreateSkybox(skybox);
	GlShader& glShader = m_GraphicsData.GetOrCreateShader(material->GetMaterialTemplate()->GetShader());

	glShader.ApplyMaterial(*material, m_GraphicsData);
	glShader.BindToUniformBuffers(m_GraphicsData.GetUniformBufferRegistry());

	glSkybox.Render();

	m_GraphicsData.ResetSamplerIndex();
}

void GlGraphicsEngine::Render(const Sprite& sprite, const Camera& camera)
{
	const Material* material = sprite.GetMaterial();
	if (!material)
		return; // TODO: LogWarning

	const MaterialTemplate* materialTemplate = material->GetMaterialTemplate();
	if (!materialTemplate)
		return; // TODO: LogWarning

	GlSprite& glSprite = m_GraphicsData.GetOrCreateSprite(sprite);
	GlShader& glShader = m_GraphicsData.GetOrCreateShader(materialTemplate->GetShader());

	glShader.ApplyMaterial(*material, m_GraphicsData);
	glShader.SetFloatMat4("modelXform", sprite.GetTransform());
	glShader.BindToUniformBuffers(m_GraphicsData.GetUniformBufferRegistry());

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
