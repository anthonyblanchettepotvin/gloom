#include <iostream>

#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Model.h"
#include "Actor.h"
#include "World.h"
#include "components/TransformComponent.h"
#include "components/ModelRendererComponent.h"
#include "components/SpriteRendererComponent.h"
#include "components/PointLightComponent.h"
#include "components/DirectionalLightComponent.h"
#include "components/OpenGLSettingsComponent.h"
#include "ui/imgui/ImGuiAdapterFactory.h"

/* UI library. */
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
/* Image loading library. */
#include "stb_image.h"

/* OpenGL functions location aren't known at compile-time.
Normally, we need to fetch each function's location at run-time
ourselves. GLAD simplify this process for us. */
/* It's important that the include to glad.h is before any other
header that require OpenGL, because it includes the required headers
behind the scenes. */
#include <glad/glad.h>
/* The creation of windows is different for each OS and
OpenGL tries to be as OS-independant as possible. So,
it's our responsibility to create the windows based on
the OS the application is running on. GLFW simplify this process for us. */
#include <GLFW/glfw3.h>
/* OpenGL Mathematics is a header-only library that implements a lot
of the required mathematics constructs and operations that we need for
graphics programming with OpenGL. */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const std::string PHONG_VERTEX_SHADER_PATH = "./shaders/phong.vs";
const std::string PHONG_FRAGMENT_SHADER_PATH = "./shaders/phong.fs";
const std::string SPRITE_VERTEX_SHADER_PATH = "./shaders/sprite.vs";
const std::string SPRITE_FRAGMENT_SHADER_PATH = "./shaders/sprite.fs";
const std::string RENDER_VERTEX_SHADER_PATH = "./shaders/render.vs";
const std::string RENDER_FRAGMENT_SHADER_PATH = "./shaders/render.fs";

// Settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 15.0f), SCR_WIDTH, SCR_HEIGHT);

// Mouse
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;	// Time between current frame and last frame.
float lastFrame = 0.0f;

// World

World world;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// The OpenGL viewport is relative to the lower left corner of the window.
	glViewport(0, 0, width, height);

	camera.setViewWidth(width);
	camera.setViewHeight(height);
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	float fxpos = static_cast<float>(xpos);
	float fypos = static_cast<float>(ypos);

	if (firstMouse)
	{
		lastX = fxpos;
		lastY = fypos;
		firstMouse = false;
	}

	float xoffset = fxpos - lastX;
	float yoffset = lastY - fypos; // Reversed since y-axis coordinates go from bottom to top.

	lastX = fxpos;
	lastY = fypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void initImGui(GLFWwindow* window);
void newImGuiFrame();
void setupImGuiFrame();
void renderImGuiFrame();
void shutdownImGui();

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);

	// glfwGetProcAddress gives us the correct OpenGL function pointers based on the OS.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

		glfwTerminate();

		return -1;
	}

	/* Tell GLFW that it should hide the cursor and capture it. Capturing a cursor
	means that, once the application has focus, the mouse cursor stays within the
	center of the window (unless the application loses focus or quits). */
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	//glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetScrollCallback(window, scrollCallback);

	initImGui(window);

	// --- Models ---

	Model backpackModel("C:\\Users\\antho\\Downloads\\backpack\\backpack.obj");

	// --- Textures ---

	Texture pointLightTexture(".\\images\\awesomeface.png", "diffuse");

	// --- Shaders ---

	Shader phongShader(PHONG_VERTEX_SHADER_PATH, PHONG_FRAGMENT_SHADER_PATH);

	phongShader.use();
	phongShader.setFloat("material.shininess", 4.0f);

	Shader spriteShader(SPRITE_VERTEX_SHADER_PATH, SPRITE_FRAGMENT_SHADER_PATH);
	
	Shader renderShader(RENDER_VERTEX_SHADER_PATH, RENDER_FRAGMENT_SHADER_PATH);

	// --- Sprite ---

	Sprite pointLightSprite(&pointLightTexture);

	// --- Actors ---

	Actor backpackActor("Backpack");

	TransformComponent backpackTransformComponent;
	backpackActor.AddComponent(&backpackTransformComponent);
	ModelRendererComponent backpackRendererComponent(&backpackModel, &phongShader);
	backpackActor.AddComponent(&backpackRendererComponent);

	Actor settingsActor("Settings");

	OpenGLSettingsComponent settingsComponent;
	settingsActor.AddComponent(&settingsComponent);

	// --- Lights ---

	Actor pointLightActor("Point light");

	TransformComponent pointLightTransformComponent(glm::vec3(2.0f));
	pointLightActor.AddComponent(&pointLightTransformComponent);
	PointLightComponent pointLightComponent;
	pointLightActor.AddComponent(&pointLightComponent);
	SpriteRendererComponent pointLightRendererComponent(&pointLightSprite, &spriteShader);
	pointLightActor.AddComponent(&pointLightRendererComponent);

	Actor directionalLightActor("Directional light");

	DirectionalLightComponent directionalLightComponent;
	directionalLightActor.AddComponent(&directionalLightComponent);

	std::vector<PointLightComponent*> pointLightComponents = {
		&pointLightComponent
	};

	std::vector<DirectionalLightComponent*> directionalLightComponents = {
		&directionalLightComponent
	};

	// --- World ---

	world.SpawnActor(&settingsActor);
	world.SpawnActor(&backpackActor);
	world.SpawnActor(&pointLightActor);
	world.SpawnActor(&directionalLightActor);

	// --- Framebuffer ---

	/* Framebuffers are useful for post-rendering effects or fancy effects like mirrors or portals.
	As usual, we generate a framebuffer object and bind it so all subsequent calls on the GL_FRAMEBUFFER
	target (or whatever target has been specified) applies to the currently bound framebuffer object. 
	When the framebuffer object is complete, all subsequent rendering calls will render into the
	currently bound framebuffer object. */
	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	/* There's two different kind of attachments: texture and renderbuffer. */
	// 1. Texture attachment
	/* We create a texture the size of our viewport and we attach the texture to the framebuffer
	as a color attachment. Note that we can attach a texture as a depth and/or stencil attachment too.
	In that case, we would need to change the texture's format accordingly. */
	Texture fboColorAttachment(SCR_WIDTH, SCR_HEIGHT);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboColorAttachment.id, 0);

	// 2. Renderbuffer attachment
	/* We create a renderbuffer the size of our viewport and we attach the renderbuffer to the framebuffer
	as a depth and stencil attachment. Note that we can attach a renderbuffer as a color attachment too. */
	/* Note that you can sample renderbuffers, but it's slow since they are optimized and designed for writing operations.
	That said, if you plan to sample the framebuffer, it's best to use texture attachments, otherwise you may want
	to use renderbuffer attachments to improve writing latency. That said, we use a renderbuffer for our depth and stencil
	attachment since we only want to sample the color attachment. */
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	/* Check if all the conditions to a complete framebuffer are met.
	The list of conditions can be found at https://learnopengl.com/Advanced-OpenGL/Framebuffers. */
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER::Framebuffer is not complete" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

	float vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// This is the render loop.
	while (!glfwWindowShouldClose(window))
	{
		// --- Pre-frame stuff ---

		/* Tells OpenGL if it should do depth testing during which it compares each fragment's z-value with the z-buffer
		and determines, based on the depth function, if the fragment passes the depth test or not. If a fragment passes
		the depth test, it will be rendered. Otherwise, it is discarded. */
		if (settingsComponent.GetDepthTestingEnabledReference())
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);

		/* Tells OpenGL which depth function to use during the depth testing. */
		switch (settingsComponent.GetDepthFunctionReference())
		{
		case OpenGLDepthFunction::ALWAYS:
			glDepthFunc(GL_ALWAYS);
			break;
		case OpenGLDepthFunction::NEVER:
			glDepthFunc(GL_NEVER);
			break;
		case OpenGLDepthFunction::LESS:
			glDepthFunc(GL_LESS);
			break;
		case OpenGLDepthFunction::EQUAL:
			glDepthFunc(GL_EQUAL);
			break;
		case OpenGLDepthFunction::LEQUAL:
			glDepthFunc(GL_LEQUAL);
			break;
		case OpenGLDepthFunction::GREATER:
			glDepthFunc(GL_GREATER);
			break;
		case OpenGLDepthFunction::NOTEQUAL:
			glDepthFunc(GL_NOTEQUAL);
			break;
		case OpenGLDepthFunction::GEQUAL:
			glDepthFunc(GL_GEQUAL);
			break;
		default:
			break;
		}

		// Update deltaTime and lastFrame.
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		/* Checks if any events are triggered (e.g., keyboard input, mouse mouvement),
		updates the window state and calls the corresponding functions. */
		glfwPollEvents();

		processInput(window);

		newImGuiFrame();
		setupImGuiFrame();

		// --- RENDERING PROCESS, STEP 1 ---
		/* During this step, we render the actual scene into our custom framebuffer. The result
		will be stored into the color attachment, which in our case is a texture. We will then
		use this texture during step 2 and render it on a quad that fits the screen perfectly. */
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		/* We need to enable depth testing on each frame since the second render pass disable it
		to make sure the quad is rendered in front of everything else. */
		glEnable(GL_DEPTH_TEST);

		// --- View and projection transformation matrices ---

		glm::mat4 viewTransform = camera.GetViewMatrix();
		glm::mat4 projectionTransform = camera.GetProjectionMatrix();

		// --- Draw actors ---

		phongShader.use();
		phongShader.setFloatMat4("viewXform", viewTransform);
		phongShader.setFloatMat4("projectionXform", projectionTransform);
		phongShader.setFloatVec3("camera.position", camera.GetPosition());

		for (size_t i = 0; i < pointLightComponents.size(); i++)
		{
			std::string identifier = "pointLights[" + std::to_string(i) + "]";

			pointLightComponents[i]->Register(&phongShader, identifier);
		}

		for (size_t i = 0; i < directionalLightComponents.size(); i++)
		{
			std::string identifier = "directionalLights[" + std::to_string(i) + "]";

			directionalLightComponents[i]->Register(&phongShader, identifier);
		}

		backpackActor.Render();

		// --- Draw lights ---

		spriteShader.use();
		spriteShader.setFloatMat4("viewXform", viewTransform);
		spriteShader.setFloatMat4("projectionXform", projectionTransform);

		pointLightActor.Render();

		// --- RENDERING PROCESS, STEP 2 ---
		/* During this step, we render a quad that fits the screen perfectly using the texture that was
		generated during step 1. */
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* We need to disable depth testing to make sure the quad is rendered in front of everything else. */
		glDisable(GL_DEPTH_TEST);

		renderShader.use();

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, fboColorAttachment.id);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// --- Post-frame stuff ---

		renderImGuiFrame();

		/* Rendering applications often have two buffers: the back and the front buffers.
		The front buffer is what is currently displayed in the viewport and the back buffer
		is used to render the current frame. When the render is done, we display the result
		by swapping the front buffer content with the back buffer content. This prevents
		artifacts like flickering, screen tearing and so on. */
		glfwSwapBuffers(window);
	}

	glDeleteFramebuffers(1, &fbo);

	shutdownImGui();

	glfwTerminate();

	return 0;
}

void initImGui(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void newImGuiFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

ImGuiAdapterFactory adapterFactory;

void setupImGuiFrame()
{
	ImGui::Begin("Controls");
	static int currentItem = -1;
	std::vector<std::string> actorsName = world.GetActorsName();
	std::vector<const char*> actorsCName;
	for (const auto& actorName : actorsName)
		actorsCName.push_back(actorName.c_str());
	ImGui::ListBox("Actors", &currentItem, actorsCName.data(), world.GetActors().size());
	ImGui::End();

	ImGui::Begin("Properties");
	if (currentItem != -1 && currentItem <= world.GetActors().size())
	{
		UiAdapter* actorAdapter = adapterFactory.CreateActorAdapter(world.GetActors()[currentItem]);
		actorAdapter->RenderUi();

		for (const auto& component : world.GetActors()[currentItem]->GetComponents())
		{
			ImGui::Separator();

			UiAdapter* componentAdapter = adapterFactory.CreateComponentAdapter(component);
			componentAdapter->RenderUi();
		}
	}
	ImGui::End();
}
void renderImGuiFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void shutdownImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
