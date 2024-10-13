#include "GlGraphicsEngine.h"

#include <glad/glad.h>

#include "../../../engine/EngineGlobals.h"
#include "../../../engine/graphics/camera/Camera.h"
#include "../../../engine/graphics/cubemap/Cubemap.h"
#include "../../../engine/graphics/lighting/DirectionalLight.h"
#include "../../../engine/graphics/lighting/PointLight.h"
#include "../../../engine/graphics/material/Material.h"
#include "../../../engine/graphics/material/MaterialAttribute.h"
#include "../../../engine/graphics/material/MaterialAttributes.h"
#include "../../../engine/graphics/mesh/Mesh.h"
#include "../../../engine/graphics/sprite/Sprite.h"
#include "../../../engine/graphics/skybox/Skybox.h"
#include "../../../engine/graphics/texture/Texture.h"
#include "../../../engine/object/ObjectID.h"

#include "GlFrame.h"
#include "GlFramebuffer.h"
#include "GlGraphicsData.h"
#include "GlRenderbufferAttachment.h"
#include "GlTextureAttachment.h"
#include "../cubemap/GlCubemap.h"
#include "../uniformbuffer/GlCameraUniformBuffer.h"
#include "../uniformbuffer/GlDirectionalLightsUniformBuffer.h"
#include "../uniformbuffer/GlMatricesUniformBuffer.h"
#include "../uniformbuffer/GlPointLightsUniformBuffer.h"
#include "../uniformbuffer/GlUniformBuffer.h"
#include "../uniformbuffer/GlUniformBufferDataTypes.h"
#include "../mesh/GlMesh.h"
#include "../shader/GlShader.h"
#include "../shader/GlShaderImporter.h"
#include "../skybox/GlSkybox.h"
#include "../sprite/GlSprite.h"
#include "../texture/GlTexture.h"

#define ERR_MSG_EXPECTS_GL_SHADER "GlGraphicsEngine expects GlShader instance."
#define ERR_MSG_MATERIAL_ATTRIBUTE_TYPE_NOT_SUPPORTED "Material attribute type is not supported."

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

	m_GraphicsData.GetTextureAttachment().RenderToFrame(m_GraphicsData.GetFrame()); // TODO: Tell, don't ask?
}

std::unique_ptr<Shader> GlGraphicsEngine::CreateShader()
{
	return std::make_unique<GlShader>();
}

std::unique_ptr<Shader> GlGraphicsEngine::ImportShader(const std::string& filePath)
{
	return GlShaderImporter().Import(filePath);
}

void GlGraphicsEngine::RegisterLight(DirectionalLight& directionalLight) // TODO: Add const to directionalLight.
{
	m_GraphicsData.RegisterLight(directionalLight);
}

void GlGraphicsEngine::RegisterLight(PointLight& pointLight) // TODO: Add const to pointLight.
{
	m_GraphicsData.RegisterLight(pointLight);
}

void GlGraphicsEngine::Render(const Camera& camera, Mesh& mesh) // TODO: Add const to mesh.
{
	if (!mesh.GetMaterial() || !mesh.GetMaterial()->GetShader())
	{
		return;
	}

	GlMesh& glMesh = m_GraphicsData.GetOrCreateMesh(mesh);
	Material* material = mesh.GetMaterial();

	ApplyMaterial(*material);

	GlShader& glShader = *(GlShader*)material->GetShader(); // TODO: Having to cast the shader to GlShader is sad.
	glShader.SetFloatMat4("modelXform", mesh.GetTransform());
	glShader.BindToUniformBuffers(m_GraphicsData.GetUniformBufferRegistry());

	UpdateUniformBuffers(camera);
	SendUniformBuffersToDevice();

	glMesh.Render();

	m_SamplerIndex = 0;
}

void GlGraphicsEngine::Render(const Camera& camera, Skybox& skybox) // TODO: Add const to skybox.
{
	if (!skybox.GetMaterial() || !skybox.GetMaterial()->GetShader())
	{
		return;
	}

	GlSkybox& glSkybox = m_GraphicsData.GetOrCreateSkybox(skybox);
	Material* material = skybox.GetMaterial();

	ApplyMaterial(*material);

	GlShader& glShader = *(GlShader*)material->GetShader(); // TODO: Having to cast the shader to GlShader is sad.
	glShader.BindToUniformBuffers(m_GraphicsData.GetUniformBufferRegistry());
	
	UpdateUniformBuffers(camera);
	SendUniformBuffersToDevice();

	glSkybox.Render();

	m_SamplerIndex = 0;
}

void GlGraphicsEngine::Render(const Camera& camera, Sprite& sprite) // TODO: Add const to sprite.
{
	if (!sprite.GetMaterial() || !sprite.GetMaterial()->GetShader())
	{
		return;
	}

	GlSprite& glSprite = m_GraphicsData.GetOrCreateSprite(sprite);
	Material* material = sprite.GetMaterial();

	ApplyMaterial(*material);

	GlShader& glShader = *(GlShader*)material->GetShader(); // TODO: Having to cast the shader to GlShader is sad.
	glShader.SetFloatMat4("modelXform", sprite.GetTransform());
	glShader.BindToUniformBuffers(m_GraphicsData.GetUniformBufferRegistry());

	UpdateUniformBuffers(camera);
	SendUniformBuffersToDevice();

	glSprite.Render();

	m_SamplerIndex = 0;
}

void* GlGraphicsEngine::GetTextureId(const Texture& texture)
{
	return (void*)m_GraphicsData.GetOrCreateTexture(texture).GetId();
}

void GlGraphicsEngine::ApplyMaterial(Material& material)
{
	if (GlShader* glShader = dynamic_cast<GlShader*>(material.GetShader()))
	{
		glShader->Use();

		for (const auto& attribute : material.GetAttributes())
		{
			ApplyMaterialAttributeToShader(*glShader, attribute);
		}
	}
	else
	{
		gLogErrorMessage(ERR_MSG_EXPECTS_GL_SHADER);
	}
}

void GlGraphicsEngine::ApplyMaterialAttributeToShader(GlShader& shader, const MaterialAttribute* attribute)
{
	if (const CubemapMaterialAttribute* cubemapAttribute = dynamic_cast<const CubemapMaterialAttribute*>(attribute))
	{
		ApplyMaterialAttributeToShader(shader, *cubemapAttribute);
	}
	else if (const FloatMaterialAttribute* floatAttribute = dynamic_cast<const FloatMaterialAttribute*>(attribute))
	{
		ApplyMaterialAttributeToShader(shader, *floatAttribute);
	}
	else if (const TextureMaterialAttribute* textureAttribute = dynamic_cast<const TextureMaterialAttribute*>(attribute))
	{
		ApplyMaterialAttributeToShader(shader, *textureAttribute);
	}
	else
	{
		gLogErrorMessage(ERR_MSG_MATERIAL_ATTRIBUTE_TYPE_NOT_SUPPORTED);
	}
}

void GlGraphicsEngine::ApplyMaterialAttributeToShader(GlShader& shader, const CubemapMaterialAttribute& attribute)
{
	const Cubemap* cubemap = attribute.GetValue();
	if (!cubemap)
	{
		return;
	}

	GlCubemap& glCubemap = m_GraphicsData.GetOrCreateCubemap(*cubemap);

	glCubemap.Use(m_SamplerIndex);
	shader.SetInt(attribute.GetName(), m_SamplerIndex);

	m_SamplerIndex++;
}

void GlGraphicsEngine::ApplyMaterialAttributeToShader(GlShader& shader, const FloatMaterialAttribute& attribute)
{
	shader.SetFloat(attribute.GetName(), attribute.GetValue());
}

void GlGraphicsEngine::ApplyMaterialAttributeToShader(GlShader& shader, const TextureMaterialAttribute& attribute)
{
	const Texture* texture = attribute.GetValue();
	if (!texture)
	{
		return;
	}

	GlTexture& glTexture = m_GraphicsData.GetOrCreateTexture(*texture);

	glTexture.Use(m_SamplerIndex);
	shader.SetInt(attribute.GetName(), m_SamplerIndex);

	m_SamplerIndex++;
}

void GlGraphicsEngine::UpdateUniformBuffers(const Camera& camera)
{
	m_GraphicsData.UpdateUniformBuffers(camera);
}

void GlGraphicsEngine::SendUniformBuffersToDevice()
{
	m_GraphicsData.SendUniformBuffersToDevice();
}
