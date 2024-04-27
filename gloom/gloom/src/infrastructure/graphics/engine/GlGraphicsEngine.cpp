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

#define EX_MSG_FRAMEBUFFER_IS_INCOMPLETE "Framebuffer is incomplete."
#define ERR_MSG_DIRECTIONAL_LIGHT_ALREADY_REGISTERED "Directional light already registered."
#define ERR_MSG_POINT_LIGHT_ALREADY_REGISTERED "Point light already registered."
#define ERR_MSG_EXPECTS_GL_SHADER "GlGraphicsEngine expects GlShader instance."
#define ERR_MSG_MATERIAL_ATTRIBUTE_TYPE_NOT_SUPPORTED "Material attribute type is not supported."

GlGraphicsEngine::GlGraphicsEngine()
{
}

GlGraphicsEngine::~GlGraphicsEngine()
{
}

void GlGraphicsEngine::Initialize(size_t width, size_t height)
{
	std::unique_ptr<GlShader> frameShader = GlShaderImporter().Import("..\\..\\assets\\shaders\\render.shader");
	m_Frame = std::make_unique<GlFrame>(frameShader);

	m_Framebuffer = std::make_unique<GlFramebuffer>(width, height);

	m_RenderbufferAttachment = std::make_unique<GlRenderbufferAttachment>(width, height);
	m_Framebuffer->AttachRenderbuffer(*m_RenderbufferAttachment);

	m_TextureAttachment = std::make_unique<GlTextureAttachment>(width, height);
	m_Framebuffer->AttachTexture(*m_TextureAttachment);

	if (!m_Framebuffer->IsComplete())
	{
		throw std::runtime_error(EX_MSG_FRAMEBUFFER_IS_INCOMPLETE);
	}

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

	InitializeUniformBuffers();
}

void GlGraphicsEngine::StartFrame()
{
	// --- RENDERING PROCESS, STEP 1 ---
	/* During this step, we render the actual scene into our custom framebuffer. The result
	will be stored into the color attachment, which in our case is a texture. We will then
	use this texture during step 2 and render it on a quad that fits the screen perfectly. */
	m_Framebuffer->Bind();

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
	m_Framebuffer->Unbind();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	/* We need to disable depth testing to make sure the quad is rendered in front of everything else. */
	//if (settingsComponent.GetDepthTestingEnabledReference())
	glDisable(GL_DEPTH_TEST);

	m_TextureAttachment->RenderToFrame(*m_Frame);
}

std::unique_ptr<Shader> GlGraphicsEngine::CreateShader()
{
	return std::make_unique<GlShader>();
}

std::unique_ptr<Shader> GlGraphicsEngine::ImportShader(const std::string& filePath)
{
	return GlShaderImporter().Import(filePath);
}

void GlGraphicsEngine::RegisterLight(DirectionalLight& directionalLight)
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

void GlGraphicsEngine::RegisterLight(PointLight& pointLight)
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

void GlGraphicsEngine::Render(const Camera& camera, Mesh& mesh)
{
	if (!mesh.GetMaterial() || !mesh.GetMaterial()->GetShader())
	{
		return;
	}

	ObjectID meshId = mesh.GetId();

	auto it = m_GlMeshes.find(meshId);
	if (it == m_GlMeshes.end())
	{
		m_GlMeshes[meshId] = std::make_unique<GlMesh>(mesh);
	}

	GlMesh& glMesh = *m_GlMeshes[meshId];

	ApplyMaterial(*mesh.GetMaterial());

	mesh.GetMaterial()->GetShader()->SetFloatMat4("modelXform", mesh.GetTransform());

	BindShaderToUniformBuffers(*(GlShader*)mesh.GetMaterial()->GetShader());
	UpdateUniformBuffers(camera);
	glMesh.Render();

	m_SamplerIndex = 0;
}

void GlGraphicsEngine::Render(const Camera& camera, Skybox& skybox)
{
	if (!skybox.GetMaterial() || !skybox.GetMaterial()->GetShader())
	{
		return;
	}

	ObjectID skyboxId = skybox.GetId();

	auto it = m_GlSkyboxes.find(skyboxId);
	if (it == m_GlSkyboxes.end())
	{
		m_GlSkyboxes[skyboxId] = std::make_unique<GlSkybox>(skybox);
	}
	
	GlSkybox& glSkybox = *m_GlSkyboxes[skyboxId];

	ApplyMaterial(*skybox.GetMaterial());

	BindShaderToUniformBuffers(*(GlShader*)skybox.GetMaterial()->GetShader());
	UpdateUniformBuffers(camera);
	glSkybox.Render();

	m_SamplerIndex = 0;
}

void GlGraphicsEngine::Render(const Camera& camera, Sprite& sprite)
{
	if (!sprite.GetMaterial() || !sprite.GetMaterial()->GetShader())
	{
		return;
	}

	ObjectID spriteId = sprite.GetId();

	auto it = m_GlSprites.find(spriteId);
	if (it == m_GlSprites.end())
	{
		m_GlSprites[spriteId] = std::make_unique<GlSprite>(sprite);
	}
	
	GlSprite& glSprite = *m_GlSprites[spriteId];

	ApplyMaterial(*sprite.GetMaterial());

	sprite.GetMaterial()->GetShader()->SetFloatMat4("modelXform", sprite.GetTransform());

	BindShaderToUniformBuffers(*(GlShader*)sprite.GetMaterial()->GetShader());
	UpdateUniformBuffers(camera);
	glSprite.Render();

	m_SamplerIndex = 0;
}

void* GlGraphicsEngine::GetTextureId(const Texture& texture)
{
	ObjectID textureId = texture.GetId();

	auto it = m_GlTextures.find(textureId);
	if (it == m_GlTextures.end())
	{
		m_GlTextures[textureId] = std::make_unique<GlTexture>(texture);
	}

	return (void*)m_GlTextures[textureId]->GetId();

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

	ObjectID cubemapId = cubemap->GetId();

	auto it = m_GlCubemaps.find(cubemapId);
	if (it == m_GlCubemaps.end())
	{
		m_GlCubemaps[cubemapId] = std::make_unique<GlCubemap>(*cubemap);
	}

	GlCubemap& glCubemap = *m_GlCubemaps[cubemapId];

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

	ObjectID textureId = texture->GetId();

	auto it = m_GlTextures.find(textureId);
	if (it == m_GlTextures.end())
	{
		m_GlTextures[textureId] = std::make_unique<GlTexture>(*texture);
	}

	GlTexture& glTexture = *m_GlTextures[textureId];

	glTexture.Use(m_SamplerIndex);
	shader.SetInt(attribute.GetName(), m_SamplerIndex);

	m_SamplerIndex++;
}

void GlGraphicsEngine::InitializeUniformBuffers()
{
	/* Here we create our Uniform Buffer Objects (UBOs). Each shader that defines a uniform
	block that matches a UBO and is bound to it will share its data. This is handy,
	since we no longer have to update the uniforms of each shader individually.
	We can only change the data in the UBO and all the shaders' uniform blocks bound
	to it will contain the updated data. */

	// Matrices UBO (128 bytes)
	/*
	MATRIX		TYPE	BASE ALIGNMENT	ALIGNED OFFSET	SIZE
	View		mat4	16				0				64
	Skybox		mat4	16				64				64
	Projection	mat4	16				128				64
	*/
	m_MatricesUniformBuffer = std::make_unique<GlMatricesUniformBuffer>();

	// Lights UBO (384 bytes)
	/*
	ELEMENT			TYPE	BASE ALIGNMENT	ALIGNED OFFSET	SIZE
	Point1			struct	16				0				72
	Point2			struct	16				80				72
	Point3			struct	16				160				72
	Point4			struct	16				240				72
	Directional		struct	16				320				60
	*/

	// PointLight struct (72 bytes)
	/*
	COMPONENT	TYPE	BASE ALIGMENT	ALIGNED OFFSET	SIZE
	position	vec3	16				0				12
	ambient		vec3	16				16				12
	diffuse		vec3	16				32				12
	specular	vec3	16				48				12
	constant	float	4				60				4
	linear		float	4				64				4
	quadratic	float	4				68				4
	*/

	// DirectionalLight struct (60 bytes)
	/*
	COMPONENT	TYPE	BASE ALIGMENT	ALIGNED OFFSET	SIZE
	direction	vec3	16				0				12
	ambient		vec3	16				16				12
	diffuse		vec3	16				32				12
	specular	vec3	16				48				12
	*/
	m_DirectionalLightsUniformBuffer = std::make_unique<GlDirectionalLightsUniformBuffer>();
	m_PointLightsUniformBuffer = std::make_unique<GlPointLightsUniformBuffer>();

	// Camera UBO (12 bytes)
	/*
	ELEMENT		TYPE	BASE ALIGNMENT	ALIGNED OFFSET	SIZE
	camera		struct	16				0				12
	*/

	// Camera struct (12 bytes)
	/*
	COMPONENT	TYPE	BASE ALIGMENT	ALIGNED OFFSET	SIZE
	position	vec3	16				0				12
	*/
	m_CameraUniformBuffer = std::make_unique<GlCameraUniformBuffer>();
}

void GlGraphicsEngine::BindShaderToUniformBuffers(GlShader& shader)
{
	// TODO: Have the shaders bind themselves to only the necessary UBOs.
	shader.BindToUniformBuffer(*m_MatricesUniformBuffer);
	shader.BindToUniformBuffer(*m_DirectionalLightsUniformBuffer);
	shader.BindToUniformBuffer(*m_PointLightsUniformBuffer);
	shader.BindToUniformBuffer(*m_CameraUniformBuffer);
}

void GlGraphicsEngine::UpdateUniformBuffers(const Camera& camera)
{
	/* Here, we update our matrices UBO data with the new matrices' data. */
	m_MatricesUniformBuffer->SetViewTransform(camera.GetViewMatrix());
	m_MatricesUniformBuffer->SetSkyboxTransform(camera.GetSkyboxMatrix());
	m_MatricesUniformBuffer->SetProjectionTransform(camera.GetProjectionMatrix());
	m_MatricesUniformBuffer->SendToDevice();

	/* Here, we update our lights UBO data with the new lights' data. */
	// TODO: Support multiple directional lights.
	if (m_DirectionalLights.size() != 0)
	{
		m_DirectionalLightsUniformBuffer->SetDirectionalLight(*m_DirectionalLights[0]);
	}
	m_DirectionalLightsUniformBuffer->SendToDevice();

	// TODO: Support multiple point lights.
	if (m_PointLights.size() != 0)
	{
		m_PointLightsUniformBuffer->SetPointLight(*m_PointLights[0]);
	}
	m_PointLightsUniformBuffer->SendToDevice();

	/* Here, we update our camera UBO data with the new camera's data. */
	m_CameraUniformBuffer->SetCameraPosition(camera.GetPosition());
	m_CameraUniformBuffer->SendToDevice();
}
