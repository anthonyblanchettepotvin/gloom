#include "GlGraphicsEngine.h"

#include <glad/glad.h>

#include "../../../engine/graphics/mesh/Mesh.h"
#include "../../../engine/graphics/sprite/Sprite.h"
#include "../../../engine/graphics/skybox/Skybox.h"

#include "../globaldata/GlGlobalData.h"
#include "../globaldata/GlGlobalDataTypes.h"
#include "../mesh/GlMesh.h"
#include "../sprite/GlSprite.h"
#include "../skybox/GlSkybox.h"

void GlGraphicsEngine::Initialize(size_t width, size_t height)
{
	m_Framebuffer = std::make_unique<GlFramebuffer>(width, height);

	Texture* texture = new Texture(width, height, 3, nullptr);
	m_RenderTexture = std::make_unique<GlTexture>(*texture);
	m_Renderbuffer = std::make_unique<GlRenderbuffer>(width, height);

	m_Framebuffer->BindTexture(*m_RenderTexture);
	m_Framebuffer->BindRenderbuffer(*m_Renderbuffer);

	if (!m_Framebuffer->CheckStatus())
	{
		// TODO: Throw incomplete framebuffer
	}

	m_RenderShader = std::move(GlShaderImporter().Import(".\\shaders\\render.shader"));
	m_RenderSurface = std::make_unique<GlRenderSurface>();

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

	m_RenderSurface->RenderTexture(*m_RenderShader, *m_RenderTexture);
}

std::unique_ptr<Shader> GlGraphicsEngine::CreateShader()
{
	return std::make_unique<GlShader>();
}

std::unique_ptr<Shader> GlGraphicsEngine::ImportShader(const std::string& filePath)
{
	return GlShaderImporter().Import(filePath);
}

GlobalData* GlGraphicsEngine::CreateGlobalData(const std::string& name) const
{
	return new GlGlobalData(name);
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, float& reference)
{
	try
	{
		GlGlobalData& glGlobalData = dynamic_cast<GlGlobalData&>(globalData);
		std::unique_ptr<GlGlobalDataType> glReference = std::make_unique<GlGlobalDataFloat>(reference);
		glGlobalData.AddDataReference(name, glReference);
	}
	catch (std::bad_cast e)
	{
		// TODO: Display error
	}
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, glm::mat4& reference)
{
	try
	{
		GlGlobalData& glGlobalData = dynamic_cast<GlGlobalData&>(globalData);
		std::unique_ptr<GlGlobalDataType> glReference = std::make_unique<GlGlobalDataMat4>(reference);
		glGlobalData.AddDataReference(name, glReference);
	}
	catch (std::bad_cast e)
	{
		// TODO: Display error
	}
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, glm::vec3& reference)
{
	try
	{
		GlGlobalData& glGlobalData = dynamic_cast<GlGlobalData&>(globalData);
		std::unique_ptr<GlGlobalDataType> glReference = std::make_unique<GlGlobalDataVec3>(reference);
		glGlobalData.AddDataReference(name, glReference);
	}
	catch (std::bad_cast e)
	{
		// TODO: Display error
	}
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, DirectionalLight& reference)
{
	try
	{
		GlGlobalData& glGlobalData = dynamic_cast<GlGlobalData&>(globalData);
		std::unique_ptr<GlGlobalDataType> glReference = std::make_unique<GlGlobalDataDirectionalLight>(reference);
		glGlobalData.AddDataReference(name, glReference);
	}
	catch (std::bad_cast e)
	{
		// TODO: Display error
	}
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(GlobalData& globalData, const std::string& name, PointLight& reference)
{
	try
	{
		GlGlobalData& glGlobalData = dynamic_cast<GlGlobalData&>(globalData);
		std::unique_ptr<GlGlobalDataType> glReference = std::make_unique<GlGlobalDataPointLight>(reference);
		glGlobalData.AddDataReference(name, glReference);
	}
	catch (std::bad_cast e)
	{
		// TODO: Display error
	}
}

void GlGraphicsEngine::Render(const Mesh& mesh)
{
	if (!mesh.GetMaterial() || !mesh.GetMaterial()->GetShader())
		return;

	ObjectID meshId = mesh.GetId();

	auto it = m_GlMeshes.find(meshId);
	if (it == m_GlMeshes.end())
	{
		m_GlMeshes[meshId] = std::make_unique<GlMesh>(mesh);
	}

	GlMesh& glMesh = *m_GlMeshes[meshId];

	ApplyMaterial(*mesh.GetMaterial());

	mesh.GetMaterial()->GetShader()->SetFloatMat4("modelXform", mesh.GetTransform());

	glMesh.Render();

	m_SamplerIndex = 0;
}

void GlGraphicsEngine::Render(const Skybox& skybox)
{
	if (!skybox.GetMaterial() || !skybox.GetMaterial()->GetShader())
		return;

	ObjectID skyboxId = skybox.GetId();

	auto it = m_GlSkyboxes.find(skyboxId);
	if (it == m_GlSkyboxes.end())
	{
		m_GlSkyboxes[skyboxId] = std::make_unique<GlSkybox>(skybox);
	}
	
	GlSkybox& glSkybox = *m_GlSkyboxes[skyboxId];

	ApplyMaterial(*skybox.GetMaterial());

	glSkybox.Render();

	m_SamplerIndex = 0;
}

void GlGraphicsEngine::Render(const Sprite& sprite)
{
	if (!sprite.GetMaterial() || !sprite.GetMaterial()->GetShader())
		return;

	ObjectID spriteId = sprite.GetId();

	auto it = m_GlSprites.find(spriteId);
	if (it == m_GlSprites.end())
	{
		m_GlSprites[spriteId] = std::make_unique<GlSprite>(sprite);
	}
	
	GlSprite& glSprite = *m_GlSprites[spriteId];

	ApplyMaterial(*sprite.GetMaterial());

	sprite.GetMaterial()->GetShader()->SetFloatMat4("modelXform", sprite.GetTransform());

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

void GlGraphicsEngine::ApplyMaterial(const Material& material)
{
	material.GetShader()->Use();

	for (const auto& attribute : material.GetAttributes())
	{
		ApplyMaterialAttributeToShader(*material.GetShader(), attribute);
	}
}

void GlGraphicsEngine::ApplyMaterialAttributeToShader(Shader& shader, MaterialAttribute* attribute)
{
	if (TextureMaterialAttribute* textureAttribute = dynamic_cast<TextureMaterialAttribute*>(attribute))
	{
		ApplyMaterialAttributeToShader(shader, textureAttribute);
	}
	else if (CubemapMaterialAttribute* cubemapAttribute = dynamic_cast<CubemapMaterialAttribute*>(attribute))
	{
		ApplyMaterialAttributeToShader(shader, cubemapAttribute);
	}
	else if (FloatMaterialAttribute* floatAttribute = dynamic_cast<FloatMaterialAttribute*>(attribute))
	{
		ApplyMaterialAttributeToShader(shader, floatAttribute);
	}

	// TODO: Display error
}

void GlGraphicsEngine::ApplyMaterialAttributeToShader(Shader& shader, TextureMaterialAttribute* attribute)
{
	Texture* texture = attribute->GetValue();
	if (!texture)
		return;

	ObjectID textureId = texture->GetId();

	auto it = m_GlTextures.find(textureId);
	if (it == m_GlTextures.end())
	{
		m_GlTextures[textureId] = std::make_unique<GlTexture>(*texture);
	}
	
	GlTexture& glTexture = *m_GlTextures[textureId];

	glTexture.Use(m_SamplerIndex);
	shader.SetInt(attribute->GetName(), m_SamplerIndex);

	m_SamplerIndex++;
}

void GlGraphicsEngine::ApplyMaterialAttributeToShader(Shader& shader, CubemapMaterialAttribute* attribute)
{
	Cubemap* cubemap = attribute->GetValue();
	if (!cubemap)
		return;

	ObjectID cubemapId = cubemap->GetId();

	auto it = m_GlCubemaps.find(cubemapId);
	if (it == m_GlCubemaps.end())
	{
		m_GlCubemaps[cubemapId] = std::make_unique<GlCubemap>(*cubemap);
	}

	GlCubemap& glCubemap = *m_GlCubemaps[cubemapId];

	glCubemap.Use(m_SamplerIndex);
	shader.SetInt(attribute->GetName(), m_SamplerIndex);

	m_SamplerIndex++;
}

void GlGraphicsEngine::ApplyMaterialAttributeToShader(Shader& shader, FloatMaterialAttribute* attribute)
{
	shader.SetFloat(attribute->GetName(), attribute->GetValue());
}
