#include "GlGraphicsData.h"

#include <glad/glad.h>

#include "../../../engine/EngineGlobals.h"
#include "../../../engine/graphics/cubemap/Cubemap.h"
#include "../../../engine/graphics/mesh/Mesh.h"
#include "../../../engine/graphics/shader/Shader.h"
#include "../../../engine/graphics/skybox/Skybox.h"
#include "../../../engine/graphics/sprite/Sprite.h"
#include "../../../engine/graphics/texture/Texture.h"

#include "../shader/GlShader.h"
#include "../uniformbuffer/GlCameraUniformBuffer.h"
#include "../uniformbuffer/GlDirectionalLightsUniformBuffer.h"
#include "../uniformbuffer/GlMatricesUniformBuffer.h"
#include "../uniformbuffer/GlPointLightsUniformBuffer.h"
#include "../uniformbuffer/GlUniformBuffer.h"

#define ERR_MSG_DIRECTIONAL_LIGHT_ALREADY_REGISTERED "Directional light already registered."
#define ERR_MSG_POINT_LIGHT_ALREADY_REGISTERED "Point light already registered."
#define EX_MSG_FRAMEBUFFER_IS_INCOMPLETE "Framebuffer is incomplete."

void GlGraphicsData::Initialize(size_t width, size_t height)
{
	m_Frame.Initialize();
	m_Framebuffer.Initialize();
	m_RenderbufferAttachment.Initialize(width, height);
	m_TextureAttachment.Initialize(width, height);

	m_Framebuffer.AttachRenderbuffer(m_RenderbufferAttachment);
	m_Framebuffer.AttachTexture(m_TextureAttachment);

	if (!m_Framebuffer.IsComplete())
	{
		throw std::runtime_error(EX_MSG_FRAMEBUFFER_IS_INCOMPLETE);
	}

	InitializeUniformBuffers();

	// --- Options ---

	/* Tells OpenGL if it should do depth testing during which it compares each fragment's z-value with the z-buffer
	and determines, based on the depth function, if the fragment passes the depth test or not. If a fragment passes
	the depth test, it will be rendered. Otherwise, it is discarded. */
	/* OpenGL draws your cube triangle-by-triangle, fragment by fragment, it will overwrite any
	pixel color that may have already been drawn there before. Since OpenGL gives no guarantee
	on the order of triangles rendered (within the same draw call), some triangles are drawn
	on top of each other even though one should clearly be in front of the other.*/
	/* Note that if we enable depth testing, we need to clear the depth buffer in each frame. */
	glEnable(GL_DEPTH_TEST);
	/* The following calls enable or disable writing to the depth buffer respectively.
	During the depth testing phase, an & (AND) operation is performed between the bit to write at
	position x in the depth buffer and the bit at position x in the depth mask. */
	glDepthMask(GL_TRUE); // enable writing the the depth buffer (1 & 1 = 1, 1 & 0 = 0)
	//glDepthMask(GL_FALSE); // disable writing to the depth buffer (0 & 1 = 0, 0 & 0 = 0)
	glDepthFunc(GL_LEQUAL);

	/* Enable stencil testing between the fragment shader execution and the depth testing phase.
	Stencil testing is similar to depth testing in the way that it discards fragments based on
	the content of a buffer, the stencil buffer. From my understanding, the stencil buffer is
	mostly programmer-defined and the depth buffer is based on the objects' position in the world. */
	glEnable(GL_STENCIL_TEST);
	/* The following calls performs the same logic as glDepthMask, but for the stencil mask. */
	//glStencilMask(GL_TRUE); // enable writing the the stencil buffer (1 & 1 = 1, 1 & 0 = 0)
	glStencilMask(GL_FALSE); // disable writing to the stencil buffer (0 & 1 = 0, 0 & 0 = 0)
	/* This tells OpenGL that whenever the stencil value of a fragment is equal (GL_EQUAL) to
	the reference value 1, the fragment passes the test and is drawn, otherwise discarded. */
	//glStencilFunc(GL_EQUAL, 1, 0xff);

	/* Enable blending. In other words, tells OpenGL to blend transparent fragments together.
	Blending happens after the stencil testing and depth testing, right when the fragment's output
	color is applied to the color buffer. The blending equation is:
	C_result = C_src_color * F_src OPERATOR C_dest_color * F_dest.*/
	glEnable(GL_BLEND);
	/* Tells OpenGL which factor to use in the blending equation. The following call tells OpenGL
	to use the source's alpha (GL_SRC_ALPHA) for the F_src variable and 1 - the source's alpha
	(GL_ONE_MINUS_SRC_ALPHA) for the F_dest variable. */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/* Tells OpenGL which operation to use in the blending equation. The following call tells OpenGL
	to use the addition operator, which is the default setting. */
	glBlendEquation(GL_FUNC_ADD);

	/* Tells OpenGL to cull (discard) the triangles that are back-faced from the viewer's point of
	view. A back-faced triangle is, by default, a triangle that has a clockwise winding order. We can disable
	momentarily face culling to render two-sided faces like grass or windows. */
	glEnable(GL_CULL_FACE);
	/* Tells OpenGL which faces we want to cull during the culling process. GL_BACK is the default setting. */
	glCullFace(GL_BACK);
	/* Tells OpenGL which winding order identifies front-faced triangles. GL_CCW is the default setting. */
	glFrontFace(GL_CCW);
}

void GlGraphicsData::RegisterLight(const DirectionalLight& directionalLight)
{
	auto it = std::find(m_DirectionalLights.begin(), m_DirectionalLights.end(), &directionalLight);
	if (it == m_DirectionalLights.end())
	{
		m_DirectionalLights.push_back(&directionalLight);
	}
	else
	{
		gLogErrorMessage(ERR_MSG_DIRECTIONAL_LIGHT_ALREADY_REGISTERED);
	}
}

void GlGraphicsData::RegisterLight(const PointLight& pointLight)
{
	auto it = std::find(m_PointLights.begin(), m_PointLights.end(), &pointLight);
	if (it == m_PointLights.end())
	{
		m_PointLights.push_back(&pointLight);
	}
	else
	{
		gLogErrorMessage(ERR_MSG_POINT_LIGHT_ALREADY_REGISTERED);
	}
}

GlCubemap& GlGraphicsData::GetOrCreateCubemap(const Cubemap& cubemap)
{
	ObjectID cubemapId = cubemap.GetId();

	auto it = m_GlCubemaps.find(cubemapId);
	if (it == m_GlCubemaps.end())
	{
		m_GlCubemaps.emplace(cubemapId, cubemap);
	}

	return m_GlCubemaps.at(cubemapId);
}

GlMesh& GlGraphicsData::GetOrCreateMesh(const Mesh& mesh)
{
	ObjectID meshId = mesh.GetId();

	auto it = m_GlMeshes.find(meshId);
	if (it == m_GlMeshes.end())
	{
		m_GlMeshes.emplace(meshId, mesh);
	}

	return m_GlMeshes.at(meshId);
}

GlShader& GlGraphicsData::GetOrCreateShader(const Shader& shader)
{
	ObjectID shaderId = shader.GetId();

	auto it = m_GlShaders.find(shaderId);
	if (it == m_GlShaders.end())
	{
		m_GlShaders.emplace(shaderId, shader);
	}

	return m_GlShaders.at(shaderId);
}

GlSkybox& GlGraphicsData::GetOrCreateSkybox(const Skybox& skybox)
{
	ObjectID skyboxId = skybox.GetId();

	auto it = m_GlSkyboxes.find(skyboxId);
	if (it == m_GlSkyboxes.end())
	{
		m_GlSkyboxes.emplace(skyboxId, skybox);
	}

	return m_GlSkyboxes.at(skyboxId);
}

GlSprite& GlGraphicsData::GetOrCreateSprite(const Sprite& sprite)
{
	ObjectID spriteId = sprite.GetId();

	auto it = m_GlSprites.find(spriteId);
	if (it == m_GlSprites.end())
	{
		m_GlSprites.emplace(spriteId, sprite);
	}

	return m_GlSprites.at(spriteId);
}

GlTexture& GlGraphicsData::GetOrCreateTexture(const Texture& texture)
{
	ObjectID textureId = texture.GetId();

	auto it = m_GlTextures.find(textureId);
	if (it == m_GlTextures.end())
	{
		m_GlTextures.emplace(textureId, texture);
	}

	return m_GlTextures.at(textureId);
}

void GlGraphicsData::UpdateUniformBuffers(const Camera& camera)
{
	for (const auto& uniformBuffer : m_UniformBufferRegistry.GetUniformBuffers())
	{
		uniformBuffer->Update(camera, *this);
	}
}

void GlGraphicsData::SendUniformBuffersToDevice()
{
	for (const auto& uniformBuffer : m_UniformBufferRegistry.GetUniformBuffers())
	{
		uniformBuffer->SendToDevice();
	}
}

void GlGraphicsData::InitializeUniformBuffers()
{
	/* Here we create our Uniform Buffer Objects (UBOs). Each shader that defines a uniform
	block that matches a UBO and is bound to it will share its data. This is handy,
	since we no longer have to update the uniforms of each shader individually.
	We can only change the data in the UBO and all the shaders' uniform blocks bound
	to it will contain the updated data. */

	// TODO: Registration should be done outside of GlGraphicsData.
	std::unique_ptr<GlUniformBuffer> matricesUniformBuffer = std::make_unique<GlMatricesUniformBuffer>();
	m_UniformBufferRegistry.Insert(matricesUniformBuffer);

	std::unique_ptr<GlUniformBuffer> directionalLightsUniformBuffer = std::make_unique<GlDirectionalLightsUniformBuffer>();
	m_UniformBufferRegistry.Insert(directionalLightsUniformBuffer);

	std::unique_ptr<GlUniformBuffer> pointLightsUniformBuffer = std::make_unique<GlPointLightsUniformBuffer>();
	m_UniformBufferRegistry.Insert(pointLightsUniformBuffer);

	std::unique_ptr<GlUniformBuffer> cameraUniformBuffer = std::make_unique<GlCameraUniformBuffer>();
	m_UniformBufferRegistry.Insert(cameraUniformBuffer);
}
