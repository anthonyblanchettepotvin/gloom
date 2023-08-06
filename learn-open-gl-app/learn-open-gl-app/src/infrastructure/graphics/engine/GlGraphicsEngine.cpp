#include "GlGraphicsEngine.h"

#include <glad/glad.h>

#include "../../../engine/graphics/rendering/primitive/Mesh.h"
#include "../../../engine/graphics/rendering/primitive/Sprite.h"
#include "../../../engine/graphics/rendering/primitive/Skybox.h"

#include "../globaldata/GlGlobalData.h"
#include "../globaldata/GlGlobalDataTypes.h"
#include "../rendering/graphicsobject/GlMesh.h"
#include "../rendering/graphicsobject/GlSprite.h"
#include "../rendering/graphicsobject/GlSkybox.h"

void GlGraphicsEngine::Initialize(size_t width, size_t height)
{
	m_Framebuffer = new GlFramebuffer(width, height);

	m_RenderTexture = new GlTexture(width, height, 3, nullptr);
	m_Renderbuffer = new GlRenderbuffer(width, height);

	m_Framebuffer->BindTexture(*m_RenderTexture);
	m_Framebuffer->BindRenderbuffer(*m_Renderbuffer);

	if (!m_Framebuffer->CheckStatus())
	{
		// TODO: Throw incomplete framebuffer
	}

	m_RenderShader = (GlShader*)m_ShaderLoader.Load(".\\shaders\\render.shader");
	m_RenderSurface = new GlRenderSurface();

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

	/*chromaticAberrationShader->Use();

	glDrawArrays(GL_TRIANGLES, 0, 6);*/
}

GlobalData* GlGraphicsEngine::CreateGlobalData(const std::string& name)
{
	return new GlGlobalData(name);
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(const std::string& name, float& reference, GlobalData* globalData)
{
	if (GlGlobalData* glGlobalData = dynamic_cast<GlGlobalData*>(globalData))
	{
		GlGlobalDataFloat* glReference = new GlGlobalDataFloat(reference);
		glGlobalData->AddDataReference(name, *glReference);
	}
	else
	{
		// TODO: Throw bad global data type exception
	}
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(const std::string& name, glm::mat4& reference, GlobalData* globalData)
{
	if (GlGlobalData* glGlobalData = dynamic_cast<GlGlobalData*>(globalData))
	{
		GlGlobalDataMat4* glReference = new GlGlobalDataMat4(reference);
		glGlobalData->AddDataReference(name, *glReference);
	}
	else
	{
		// TODO: Throw bad global data type exception
	}
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(const std::string& name, glm::vec3& reference, GlobalData* globalData)
{
	if (GlGlobalData* glGlobalData = dynamic_cast<GlGlobalData*>(globalData))
	{
		GlGlobalDataVec3* glReference = new GlGlobalDataVec3(reference);
		glGlobalData->AddDataReference(name, *glReference);
	}
	else
	{
		// TODO: Throw bad global data type exception
	}
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(const std::string& name, DirectionalLight& reference, GlobalData* globalData)
{
	if (GlGlobalData* glGlobalData = dynamic_cast<GlGlobalData*>(globalData))
	{
		GlGlobalDataDirectionalLight* glReference = new GlGlobalDataDirectionalLight(reference);
		glGlobalData->AddDataReference(name, *glReference);
	}
	else
	{
		// TODO: Throw bad global data type exception
	}
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(const std::string& name, PointLight& reference, GlobalData* globalData)
{
	if (GlGlobalData* glGlobalData = dynamic_cast<GlGlobalData*>(globalData))
	{
		GlGlobalDataPointLight* glReference = new GlGlobalDataPointLight(reference);
		glGlobalData->AddDataReference(name, *glReference);
	}
	else
	{
		// TODO: Throw bad global data type exception
	}
}

void GlGraphicsEngine::RenderPrimitive(RenderingPrimitive& primitive)
{

	GraphicsObject* graphicsObject = primitive.GetGraphicsObject();

	// TODO: Implement a factory for making the right GraphicsObject
	if (!graphicsObject)
	{
		try
		{
			Mesh& mesh = dynamic_cast<Mesh&>(primitive);
			graphicsObject = new GlMesh(mesh);
			mesh.SetGraphicsObject(graphicsObject);
		}
		catch (std::bad_cast)
		{
		}
	}

	if (!graphicsObject)
	{
		try
		{
			Sprite& sprite = dynamic_cast<Sprite&>(primitive);
			graphicsObject = new GlSprite(sprite);
			sprite.SetGraphicsObject(graphicsObject);
		}
		catch (std::bad_cast)
		{
		}
	}

	if (!graphicsObject)
	{
		try
		{
			Skybox& skybox = dynamic_cast<Skybox&>(primitive);
			graphicsObject = new GlSkybox(skybox);
			skybox.SetGraphicsObject(graphicsObject);
		}
		catch (std::bad_cast)
		{
		}
	}

	if (graphicsObject)
	{
		graphicsObject->Render();
	}
}
