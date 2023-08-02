#include <iostream>

#include "engine/graphics/model/Model.h"
#include "engine/graphics/engine/GraphicsEngine.h"
#include "engine/graphics/lighting/Skybox.h"
#include "engine/graphics/shader/Shader.h"
#include "engine/graphics/shader/ShaderLoader.h"
#include "engine/graphics/texture/Cubemap.h"
#include "engine/graphics/texture/CubemapLoader.h"
#include "engine/graphics/texture/Sprite.h"
#include "engine/graphics/texture/TextureLoader.h"
#include "game/actor/Actor.h"
#include "game/camera/Camera.h"
#include "game/component/TransformComponent.h"
#include "game/component/ModelRendererComponent.h"
#include "game/component/SkyboxRendererComponent.h"
#include "game/component/SpriteRendererComponent.h"
#include "game/component/PointLightComponent.h"
#include "game/component/DirectionalLightComponent.h"
#include "game/world/World.h"
#include "infrastructure/graphics/engine/GlGraphicsEngine.h"
#include "infrastructure/graphics/lighting/GlSkybox.h"
#include "infrastructure/graphics/model/GlModelLoader.h"
#include "infrastructure/graphics/shader/GlShaderLoader.h"
#include "infrastructure/graphics/texture/GlCubemapLoader.h"
#include "infrastructure/graphics/texture/GlSprite.h"
#include "infrastructure/graphics/texture/GlTexture.h"
#include "infrastructure/graphics/texture/GlTextureLoader.h"
#include "ui/imgui/ImGuiAdapterFactory.h"

/* UI library. */
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
/* Image loading library. */
#include "vendor/stbi/stb_image.h"

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

const std::string PHONG_SHADER_PATH = ".\\shaders\\phong.shader";
const std::string REFLECTION_SHADER_PATH = ".\\shaders\\reflection.shader";
const std::string REFRACTION_SHADER_PATH = ".\\shaders\\refraction.shader";
const std::string SPRITE_SHADER_PATH = ".\\shaders\\sprite.shader";
const std::string RENDER_SHADER_PATH = ".\\shaders\\render.shader";
const std::string SKYBOX_SHADER_PATH = ".\\shaders\\skybox.shader";
const std::string CHROMATIC_ABERRATION_SHADER_PATH = ".\\shaders\\chromatic_aberration.shader";

const std::string BACKPACK_MODEL_PATH = ".\\models\\backpack\\backpack.obj";
const std::string CUBE_MODEL_PATH = ".\\models\\cube\\cube.obj";
const std::string SUZANNE_MODEL_PATH = ".\\models\\suzanne\\suzanne.obj";

const std::string AWESOME_EMOJI_TEXTURE_PATH = ".\\images\\awesomeface.png";

const std::vector<std::string> CUBEMAP_FACES_PATH = {
		".\\images\\nightCubemap\\posx.jpg",
		".\\images\\nightCubemap\\negx.jpg",
		".\\images\\nightCubemap\\posy.jpg",
		".\\images\\nightCubemap\\negy.jpg",
		".\\images\\nightCubemap\\posz.jpg",
		".\\images\\nightCubemap\\negz.jpg"
};

// Settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

// Camera
bool cameraMode = false;
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
	if (!cameraMode)
		return;

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
	if (!cameraMode)
		return;

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

	cameraMode = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;

	if (!cameraMode)
		return;

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

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetScrollCallback(window, scrollCallback);

	initImGui(window);

	// --- Graphics ---

	GraphicsEngine* graphicsEngine = new GlGraphicsEngine();
	graphicsEngine->Initialize(SCR_WIDTH, SCR_HEIGHT);

	// --- Models ---

	Model* backpackModel = graphicsEngine->GetModelLoader().Load(BACKPACK_MODEL_PATH);
	Shader* backpackShader = graphicsEngine->GetShaderLoader().Load(PHONG_SHADER_PATH);
	backpackShader->Use();
	backpackShader->SetFloat("material.shininess", 4.0f);

	Model* cubeModel = graphicsEngine->GetModelLoader().Load(CUBE_MODEL_PATH);
	Shader* cubeShader = graphicsEngine->GetShaderLoader().Load(REFLECTION_SHADER_PATH);

	Model* suzanneModel = graphicsEngine->GetModelLoader().Load(SUZANNE_MODEL_PATH);
	Shader* suzanneShader = graphicsEngine->GetShaderLoader().Load(REFRACTION_SHADER_PATH);

	// --- Textures ---

	Texture* pointLightTexture = graphicsEngine->GetTextureLoader().Load(AWESOME_EMOJI_TEXTURE_PATH);

	// --- Cubemaps ---

	Cubemap* cubemap = graphicsEngine->GetCubemapLoader().Load(CUBEMAP_FACES_PATH);

	// --- Skyboxes ---

	Skybox* skybox = new GlSkybox(cubemap);

	// --- Shaders ---

	Shader* spriteShader = graphicsEngine->GetShaderLoader().Load(SPRITE_SHADER_PATH);
	Shader* renderShader = graphicsEngine->GetShaderLoader().Load(RENDER_SHADER_PATH);
	Shader* skyboxShader = graphicsEngine->GetShaderLoader().Load(SKYBOX_SHADER_PATH);
	Shader* chromaticAberrationShader = graphicsEngine->GetShaderLoader().Load(CHROMATIC_ABERRATION_SHADER_PATH);

	// --- Sprite ---

	Sprite* pointLightSprite = new GlSprite(pointLightTexture);

	// --- Actors ---

	Actor skyboxActor("Skybox");

	SkyboxRendererComponent skyboxRendererComponent(skybox, skyboxShader);
	skyboxActor.AddComponent(&skyboxRendererComponent);

	Actor backpackActor("Backpack");

	TransformComponent backpackTransformComponent;
	backpackActor.AddComponent(&backpackTransformComponent);
	ModelRendererComponent backpackRendererComponent(backpackModel, backpackShader);
	backpackActor.AddComponent(&backpackRendererComponent);

	Actor cubeActor("Cube");

	TransformComponent cubeTransformComponent(glm::vec3(-4.0f, 0.0f, 0.0f));
	cubeActor.AddComponent(&cubeTransformComponent);
	ModelRendererComponent cubeRendererComponent(cubeModel, cubeShader);
	cubeActor.AddComponent(&cubeRendererComponent);

	Actor suzanneActor("Suzanne");

	TransformComponent suzanneTransformComponent(glm::vec3(0.0f, 0.0f, 2.0f));
	suzanneActor.AddComponent(&suzanneTransformComponent);
	ModelRendererComponent suzanneRendererComponent(suzanneModel, suzanneShader);
	suzanneActor.AddComponent(&suzanneRendererComponent);

	// --- Lights ---

	Actor pointLightActor("Point light");

	PointLight pointLight(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f), {1.0f, 0.14f, 0.07f});

	TransformComponent pointLightTransformComponent(glm::vec3(2.0f));
	pointLightActor.AddComponent(&pointLightTransformComponent);
	PointLightComponent pointLightComponent(&pointLight);
	pointLightActor.AddComponent(&pointLightComponent);
	SpriteRendererComponent pointLightRendererComponent(pointLightSprite, spriteShader);
	pointLightActor.AddComponent(&pointLightRendererComponent);

	Actor directionalLightActor("Directional light");

	DirectionalLight directionalLight(glm::vec3(0.05f), glm::vec3(0.4f), glm::vec3(0.5f));

	DirectionalLightComponent directionalLightComponent(&directionalLight);
	directionalLightActor.AddComponent(&directionalLightComponent);

	std::vector<PointLightComponent*> pointLightComponents = {
		&pointLightComponent
	};

	std::vector<DirectionalLightComponent*> directionalLightComponents = {
		&directionalLightComponent
	};

	// --- World ---

	world.SpawnActor(&skyboxActor);
	world.SpawnActor(&backpackActor);
	world.SpawnActor(&cubeActor);
	world.SpawnActor(&suzanneActor);
	world.SpawnActor(&pointLightActor);
	world.SpawnActor(&directionalLightActor);

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
	glm::mat4 viewTransform;
	glm::mat4 skyboxTransform;
	glm::mat4 projectionTransform;
	GlobalData* matricesGlobalData = graphicsEngine->CreateGlobalData("ubo_matrices");
	graphicsEngine->AddDataReferenceToGlobalData("view", viewTransform, matricesGlobalData);
	graphicsEngine->AddDataReferenceToGlobalData("skybox", skyboxTransform, matricesGlobalData);
	graphicsEngine->AddDataReferenceToGlobalData("projection", projectionTransform, matricesGlobalData);

	/* Here, we bind the corresponding uniform block of each of our shaders to the matrices UBO. */
	backpackShader->BindToGlobalData(matricesGlobalData);
	cubeShader->BindToGlobalData(matricesGlobalData);
	suzanneShader->BindToGlobalData(matricesGlobalData);
	skyboxShader->BindToGlobalData(matricesGlobalData);
	spriteShader->BindToGlobalData(matricesGlobalData);

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
	GlobalData* directionalLightsGlobalData = graphicsEngine->CreateGlobalData("ubo_directionalLights");
	graphicsEngine->AddDataReferenceToGlobalData("directionalLight1", directionalLight, directionalLightsGlobalData);
	GlobalData* pointLightsGlobalData = graphicsEngine->CreateGlobalData("ubo_pointLights");
	graphicsEngine->AddDataReferenceToGlobalData("pointLight1", pointLight, pointLightsGlobalData);

	backpackShader->BindToGlobalData(directionalLightsGlobalData);
	backpackShader->BindToGlobalData(pointLightsGlobalData);

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
	glm::vec3 cameraPosition;
	GlobalData* cameraGlobalData = graphicsEngine->CreateGlobalData("ubo_camera");
	graphicsEngine->AddDataReferenceToGlobalData("camera", cameraPosition, cameraGlobalData);

	backpackShader->BindToGlobalData(cameraGlobalData);
	cubeShader->BindToGlobalData(cameraGlobalData);
	suzanneShader->BindToGlobalData(cameraGlobalData);

	// This is the render loop.
	while (!glfwWindowShouldClose(window))
	{
		// --- Pre-frame stuff ---
		
		// Update deltaTime and lastFrame.
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		/* Checks if any events are triggered (e.g., keyboard input, mouse mouvement),
		updates the window state and calls the corresponding functions. */
		glfwPollEvents();

		processInput(window);

		if (cameraMode)
			/* Tell GLFW that it should hide the cursor and capture it. Capturing a cursor
			means that, once the application has focus, the mouse cursor stays within the
			center of the window (unless the application loses focus or quits). */
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		newImGuiFrame();
		setupImGuiFrame();

		graphicsEngine->StartFrame();

		// --- View and projection transformation matrices ---

		/* Here, we update our matrices UBO data with the new matrices' data. */
		viewTransform = camera.GetViewMatrix();
		skyboxTransform = camera.GetSkyboxMatrix();
		projectionTransform = camera.GetProjectionMatrix();
		matricesGlobalData->SendToDevice();

		/* Here, we update our camera UBO data with the new camera's data. */
		cameraPosition = camera.GetPosition();
		cameraGlobalData->SendToDevice();

		/* Here, we update our lights UBO data with the new lights' data. */
		directionalLightsGlobalData->SendToDevice();
		pointLightsGlobalData->SendToDevice();

		// --- Draw actors ---

		backpackActor.Render();
		cubeActor.Render();
		suzanneActor.Render();
		/* We could've render the skybox first, but we would render fragments that might be overridden
		by the rest of the scene. Knowing that, we render it last and by exploiting depth testing - see
		comments in the skybox vertex shader -, still make it look like it's behind everything. Plus,
		using this neat little trick, we don't have to call glDepthMask with GL_FALSE before rendering the
		skybox and then call it again with GL_TRUE. */
		skyboxActor.Render();
		/* We need to render the actors with transparency last. */
		pointLightActor.Render();

		graphicsEngine->EndFrame();

		// --- Post-frame stuff ---

		renderImGuiFrame();

		/* Rendering applications often have two buffers: the back and the front buffers.
		The front buffer is what is currently displayed in the viewport and the back buffer
		is used to render the current frame. When the render is done, we display the result
		by swapping the front buffer content with the back buffer content. This prevents
		artifacts like flickering, screen tearing and so on. */
		glfwSwapBuffers(window);
	}

	shutdownImGui();

	glfwTerminate();

	// TODO: Delete models, textures, etc.

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
		if (actorAdapter)
		{
			actorAdapter->RenderUi();
		}

		for (const auto& component : world.GetActors()[currentItem]->GetComponents())
		{
			ImGui::Separator();

			UiAdapter* componentAdapter = adapterFactory.CreateComponentAdapter(component);
			if (componentAdapter)
			{
				componentAdapter->RenderUi();
			}
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
