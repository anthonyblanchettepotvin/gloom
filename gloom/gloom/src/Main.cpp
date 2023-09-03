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

/* UI library. */
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
/* Image loading library. */
#include "vendor/stbi/stb_image.h"

#include "application/ApplicationManager.h"
#include "engine/EngineGlobals.h"
#include "engine/asset/Asset.h"
#include "engine/asset/AssetDescriptor.h"
#include "engine/asset/AssetFactory.h"
#include "engine/asset/AssetManager.h"
#include "engine/asset/AssetRegistry.h"
#include "engine/asset/AssetRepository.h"
#include "engine/graphics/camera/Camera.h"
#include "engine/graphics/cubemap/Cubemap.h"
#include "engine/graphics/engine/GraphicsEngine.h"
#include "engine/graphics/globaldata/GlobalData.h"
#include "engine/graphics/lighting/DirectionalLight.h"
#include "engine/graphics/lighting/PointLight.h"
#include "engine/graphics/material/Material.h"
#include "engine/graphics/material/MaterialAttribute.h"
#include "engine/graphics/material/MaterialAttributes.h"
#include "engine/graphics/model/Model.h"
#include "engine/graphics/shader/Shader.h"
#include "engine/graphics/shader/ShaderRegistry.h"
#include "engine/graphics/skybox/Skybox.h"
#include "engine/graphics/sprite/Sprite.h"
#include "engine/graphics/texture/Texture.h"
#include "engine/util/logging/LoggerRepository.h"
#include "engine/util/logging/LoggingManager.h"
#include "game/actor/Actor.h"
#include "game/component/DirectionalLightComponent.h"
#include "game/component/ModelRendererComponent.h"
#include "game/component/PointLightComponent.h"
#include "game/component/SkyboxRendererComponent.h"
#include "game/component/SpriteRendererComponent.h"
#include "game/component/TransformComponent.h"
#include "game/GameManager.h"
#include "game/world/World.h"
#include "infrastructure/asset/cubemap/CubemapAssetFactory.h"
#include "infrastructure/asset/cubemap/CubemapImporter.h"
#include "infrastructure/asset/material/MaterialAssetFactory.h"
#include "infrastructure/asset/model/ModelAssetFactory.h"
#include "infrastructure/asset/model/ModelImporter.h"
#include "infrastructure/asset/shader/ShaderAssetFactory.h"
#include "infrastructure/asset/shader/ShaderImporter.h"
#include "infrastructure/asset/texture/TextureAssetFactory.h"
#include "infrastructure/asset/texture/TextureImporter.h"
#include "infrastructure/asset/world/WorldAssetFactory.h"
#include "infrastructure/graphics/engine/GlGraphicsEngine.h"
#include "infrastructure/graphics/shader/GlShader.h"
#include "infrastructure/graphics/shader/GlShaderImporter.h"
#include "ui/imgui/ImGuiMain.h"

#define LOGGER_KEY "main"
#define ERR_MSG_GLFW_WINDOW_CREATION_FAILED "Failed to create GLFW window."
#define ERR_MSG_GLAD_INITIALIZATION_FAILED "Failed to initialize GLAD."

const std::string LOGO_IMAGE_PATH = "..\\..\\assets\\images\\gloom_logo_g_64.png";

const std::string CHROMATIC_ABERRATION_SHADER_PATH = "..\\..\\assets\\shaders\\chromatic_aberration.shader";
const std::string PHONG_SHADER_PATH = "..\\..\\assets\\shaders\\phong.shader";
const std::string REFLECTION_SHADER_PATH = "..\\..\\assets\\shaders\\reflection.shader";
const std::string REFRACTION_SHADER_PATH = "..\\..\\assets\\shaders\\refraction.shader";
const std::string RENDER_SHADER_PATH = "..\\..\\assets\\shaders\\render.shader";
const std::string SKYBOX_SHADER_PATH = "..\\..\\assets\\shaders\\skybox.shader";
const std::string SPRITE_SHADER_PATH = "..\\..\\assets\\shaders\\sprite.shader";

const std::string BACKPACK_MODEL_PATH = "..\\..\\assets\\models\\backpack\\backpack.obj";
const std::string CUBE_MODEL_PATH = "..\\..\\assets\\models\\cube\\cube.obj";
const std::string SUZANNE_MODEL_PATH = "..\\..\\assets\\models\\suzanne\\suzanne.obj";

const std::string AWESOME_EMOJI_TEXTURE_PATH = "..\\..\\assets\\images\\awesomeface.png";

const std::vector<std::string> CUBEMAP_FACES_PATH = {
	"..\\..\\assets\\images\\nightCubemap\\1.jpg",
	"..\\..\\assets\\images\\nightCubemap\\2.jpg",
	"..\\..\\assets\\images\\nightCubemap\\3.jpg",
	"..\\..\\assets\\images\\nightCubemap\\4.jpg",
	"..\\..\\assets\\images\\nightCubemap\\5.jpg",
	"..\\..\\assets\\images\\nightCubemap\\6.jpg"
};

// Settings
const size_t SCR_WIDTH = 1600;
const size_t SCR_HEIGHT = 900;

// Camera
bool g_CameraMode = false;
Camera g_Camera(glm::vec3(0.0f, 0.0f, 15.0f), SCR_WIDTH, SCR_HEIGHT);

// Mouse
float g_MouseLastX = SCR_WIDTH / 2.0f;
float g_MouseLastY = SCR_HEIGHT / 2.0f;
bool g_MouseLastPositionInitialized = false;

// Timing
float g_DeltaTime = 0.0f; // Time between current frame and last frame.
float g_LastFrameTime = 0.0f;

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// The OpenGL viewport is relative to the lower left corner of the window.
	glViewport(0, 0, width, height);

	g_Camera.SetViewWidth(width);
	g_Camera.SetViewHeight(height);
}

void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (!g_CameraMode)
	{
		return;
	}

	float fxpos = (float)xpos;
	float fypos = (float)ypos;

	if (!g_MouseLastPositionInitialized)
	{
		g_MouseLastX = fxpos;
		g_MouseLastY = fypos;
		g_MouseLastPositionInitialized = true;
	}

	float xoffset = fxpos - g_MouseLastX;
	float yoffset = g_MouseLastY - fypos; // Reversed since y-axis coordinates go from bottom to top.

	g_MouseLastX = fxpos;
	g_MouseLastY = fypos;

	g_Camera.ProcessMouseMovement(xoffset, yoffset);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (!g_CameraMode)
	{
		return;
	}

	g_Camera.ProcessMouseScroll((float)yoffset);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	g_CameraMode = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;

	if (!g_CameraMode)
	{
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		g_Camera.ProcessKeyboard(FORWARD, g_DeltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		g_Camera.ProcessKeyboard(BACKWARD, g_DeltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		g_Camera.ProcessKeyboard(LEFT, g_DeltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		g_Camera.ProcessKeyboard(RIGHT, g_DeltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		g_Camera.ProcessKeyboard(UP, g_DeltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		g_Camera.ProcessKeyboard(DOWN, g_DeltaTime);
	}
}

void InitImGui(GLFWwindow* window);
void NewImGuiFrame();
void RenderImGuiFrame();
void ShutdownImGui();

int main()
{
	LoggerRepository loggerRepository;
	LoggingManager loggingManager(loggerRepository);

	std::unique_ptr<EngineGlobalsInstance> engineGlobalsInstance = std::make_unique<EngineGlobalsInstance>(loggingManager);
	EngineGlobals::SetInstance(engineGlobalsInstance);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Gloom", nullptr, nullptr);
	if (!window)
	{
		gLogErrorMessageForKey(LOGGER_KEY, ERR_MSG_GLFW_WINDOW_CREATION_FAILED);

		glfwTerminate();

		return -1;
	}

	GLFWimage windowIcons[1];
	windowIcons[0].pixels = stbi_load(LOGO_IMAGE_PATH.c_str(), &windowIcons[0].width, &windowIcons[0].height, NULL, 4);
	glfwSetWindowIcon(window, 1, windowIcons);
	stbi_image_free(windowIcons[0].pixels);

	glfwMakeContextCurrent(window);

	// glfwGetProcAddress gives us the correct OpenGL function pointers based on the OS.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		gLogErrorMessageForKey(LOGGER_KEY, ERR_MSG_GLAD_INITIALIZATION_FAILED);

		glfwTerminate();

		return -1;
	}

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetCursorPosCallback(window, CursorPosCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	InitImGui(window);

	// --- Graphics Engine ---

	GlGraphicsEngine graphicsEngine;
	graphicsEngine.Initialize(SCR_WIDTH, SCR_HEIGHT);

	// --- Application Manager ---

	ApplicationManager applicationManager;

	// --- Game Manager ---

	GameManager gameManager;

	// --- Asset Manager ---

	AssetRegistry assetRegistry;
	AssetRepository assetRepository;

	AssetManager assetManager(assetRegistry, assetRepository);

	// --- Importers ---

	CubemapImporter cubemapImporter(assetManager);
	TextureImporter textureImporter(assetManager);
	ShaderImporter shaderImporter(assetManager, graphicsEngine);
	ShaderRegistry shaderRegistry;
	ModelImporter modelImporter(assetManager, textureImporter, shaderRegistry);

	// --- Asset Descriptors ---

	// Texture
	AssetDescriptor textureAssetDescriptor(ObjectType(typeid(Texture)), "Texture");
	std::unique_ptr<AssetFactory> textureAssetFactory = std::make_unique<TextureAssetFactory>();
	assetRegistry.DefineAsset(textureAssetDescriptor, textureAssetFactory);

	// Material
	AssetDescriptor materialAssetDescriptor(ObjectType(typeid(Material)), "Material");
	std::unique_ptr<AssetFactory> materialAssetFactory = std::make_unique<MaterialAssetFactory>();
	assetRegistry.DefineAsset(materialAssetDescriptor, materialAssetFactory);

	// Model
	AssetDescriptor modelAssetDescriptor(ObjectType(typeid(Model)), "Model");
	std::unique_ptr<AssetFactory> modelAssetFactory = std::make_unique<ModelAssetFactory>();
	assetRegistry.DefineAsset(modelAssetDescriptor, modelAssetFactory);

	// Cubemap
	AssetDescriptor cubemapAssetDescriptor(ObjectType(typeid(Cubemap)), "Cubemap");
	std::unique_ptr<AssetFactory> cubemapAssetFactory = std::make_unique<CubemapAssetFactory>();
	assetRegistry.DefineAsset(cubemapAssetDescriptor, cubemapAssetFactory);

	// Shader
	AssetDescriptor shaderAssetDescriptor(ObjectType(typeid(GlShader)), "Shader");
	std::unique_ptr<AssetFactory> shaderAssetFactory = std::make_unique<ShaderAssetFactory>(graphicsEngine);
	assetRegistry.DefineAsset(shaderAssetDescriptor, shaderAssetFactory);

	// World
	AssetDescriptor worldAssetDescriptor(ObjectType(typeid(World)), "World");
	std::unique_ptr<AssetFactory> worldAssetFactory = std::make_unique<WorldAssetFactory>();
	assetRegistry.DefineAsset(worldAssetDescriptor, worldAssetFactory);

	// --- Shaders ---

	Asset* phongShaderAsset = shaderImporter.Import("Phong", PHONG_SHADER_PATH);
	Shader* phongShader = (Shader*)phongShaderAsset->GetObject();

	Asset* reflectionShaderAsset = shaderImporter.Import("Reflection", REFLECTION_SHADER_PATH);
	Shader* reflectionShader = (Shader*)reflectionShaderAsset->GetObject();
	
	Asset* refractionShaderAsset = shaderImporter.Import("Refraction", REFRACTION_SHADER_PATH);
	Shader* refractionShader = (Shader*)refractionShaderAsset->GetObject();
	
	Asset* spriteShaderAsset = shaderImporter.Import("Sprite", SPRITE_SHADER_PATH);
	Shader* spriteShader = (Shader*)spriteShaderAsset->GetObject();
	
	Asset* renderShaderAsset = shaderImporter.Import("Render", RENDER_SHADER_PATH);
	Shader* renderShader = (Shader*)renderShaderAsset->GetObject();
	
	Asset* skyboxShaderAsset = shaderImporter.Import("Skybox", SKYBOX_SHADER_PATH);
	Shader* skyboxShader = (Shader*)skyboxShaderAsset->GetObject();
	
	Asset* chromaticAberrationShaderAsset = shaderImporter.Import("ChromaticAberration", CHROMATIC_ABERRATION_SHADER_PATH);
	Shader* chromaticAberrationShader = (Shader*)chromaticAberrationShaderAsset->GetObject();

	shaderRegistry.Register(ShadingModel::Phong, *phongShader);

	// --- Textures ---

	Asset* pointLightTextureAsset = textureImporter.Import("AwesomeEmoji", AWESOME_EMOJI_TEXTURE_PATH);
	Texture* pointLightTexture = (Texture*)pointLightTextureAsset->GetObject();

	// --- Models ---

	Asset* backpackModelAsset = modelImporter.Import("Backpack", BACKPACK_MODEL_PATH);
	Model* backpackModel = (Model*)backpackModelAsset->GetObject();

	Asset* testModelAsset = modelImporter.Import("Cube", CUBE_MODEL_PATH);
	Model* testModel = (Model*)testModelAsset->GetObject();

	Asset* cubeModelAsset = modelImporter.Import("Cube", CUBE_MODEL_PATH);
	Model* cubeModel = (Model*)cubeModelAsset->GetObject();

	Asset* suzanneModelAsset = modelImporter.Import("Suzanne", SUZANNE_MODEL_PATH);
	Model* suzanneModel = (Model*)suzanneModelAsset->GetObject();

	Material* testModelMaterial = phongShader->CreateMaterialInstance();

	TextureMaterialAttribute* testDiffuseAttribute = testModelMaterial->FindAttribute<TextureMaterialAttribute>("material.texture_diffuse1");
	if (testDiffuseAttribute)
	{
		testDiffuseAttribute->SetValue(pointLightTexture);
	}

	TextureMaterialAttribute* testSpecularAttribute = testModelMaterial->FindAttribute<TextureMaterialAttribute>("material.texture_specular1");
	if (testSpecularAttribute)
	{
		testSpecularAttribute->SetValue(pointLightTexture);
	}

	FloatMaterialAttribute* testShininessAttribute = testModelMaterial->FindAttribute<FloatMaterialAttribute>("material.shininess");
	if (testShininessAttribute)
	{
		testShininessAttribute->SetValue(4.0f);
	}

	testModel->SetMaterial(testModelMaterial);

	Material* reflectionMaterial = reflectionShader->CreateMaterialInstance();
	cubeModel->SetMaterial(reflectionMaterial);

	Material* refractionMaterial = refractionShader->CreateMaterialInstance();
	suzanneModel->SetMaterial(refractionMaterial);

	// --- Cubemaps ---

	Asset* cubemapAsset = cubemapImporter.Import("Cubemap", CUBEMAP_FACES_PATH);
	Cubemap* cubemap = (Cubemap*)cubemapAsset->GetObject();

	// --- Skyboxes ---

	Material* skyboxMaterial = skyboxShader->CreateMaterialInstance();

	CubemapMaterialAttribute* skyboxCubemapAttribute = skyboxMaterial->FindAttribute<CubemapMaterialAttribute>("material.cubemap_skybox");
	if (skyboxCubemapAttribute)
	{
		skyboxCubemapAttribute->SetValue(cubemap);
	}

	Skybox* skybox = new Skybox(skyboxMaterial);

	// --- Sprite ---

	Material* pointLightSpriteMaterial = spriteShader->CreateMaterialInstance();

	TextureMaterialAttribute* pointLightTextureAttribute = pointLightSpriteMaterial->FindAttribute<TextureMaterialAttribute>("material.texture_sprite");
	if (pointLightTextureAttribute)
	{
		pointLightTextureAttribute->SetValue(pointLightTexture);
	}

	Sprite* pointLightSprite = new Sprite(pointLightSpriteMaterial);

	// --- Actors ---

	Actor skyboxActor("Skybox");

	std::unique_ptr<ActorComponent> skyboxRendererComponent = std::make_unique<SkyboxRendererComponent>(graphicsEngine, skybox);
	skyboxActor.AddComponent(skyboxRendererComponent);

	Actor backpackActor("Backpack");

	std::unique_ptr<ActorComponent> backpackTransformComponent = std::make_unique<TransformComponent>();
	backpackActor.AddComponent(backpackTransformComponent);
	std::unique_ptr<ActorComponent> backpackRendererComponent = std::make_unique<ModelRendererComponent>(graphicsEngine, backpackModel);
	backpackActor.AddComponent(backpackRendererComponent);

	Actor testActor("Test");

	std::unique_ptr<ActorComponent> testTransformComponent = std::make_unique<TransformComponent>(glm::vec3(4.0f, 0.0f, 0.0f));
	testActor.AddComponent(testTransformComponent);
	std::unique_ptr<ActorComponent> testRendererComponent = std::make_unique<ModelRendererComponent>(graphicsEngine, testModel);
	testActor.AddComponent(testRendererComponent);

	Actor cubeActor("Cube");

	std::unique_ptr<ActorComponent> cubeTransformComponent = std::make_unique<TransformComponent>(glm::vec3(-4.0f, 0.0f, 0.0f));
	cubeActor.AddComponent(cubeTransformComponent);
	std::unique_ptr<ActorComponent> cubeRendererComponent = std::make_unique<ModelRendererComponent>(graphicsEngine, cubeModel);
	cubeActor.AddComponent(cubeRendererComponent);

	Actor suzanneActor("Suzanne");

	std::unique_ptr<ActorComponent> suzanneTransformComponent = std::make_unique<TransformComponent>(glm::vec3(0.0f, 0.0f, 2.0f));
	suzanneActor.AddComponent(suzanneTransformComponent);
	std::unique_ptr<ActorComponent> suzanneRendererComponent = std::make_unique<ModelRendererComponent>(graphicsEngine, suzanneModel);
	suzanneActor.AddComponent(suzanneRendererComponent);

	// --- Lights ---

	Actor pointLightActor("Point light");

	PointLight pointLight(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f), { 1.0f, 0.14f, 0.07f });

	std::unique_ptr<ActorComponent> pointLightTransformComponent = std::make_unique<TransformComponent>(glm::vec3(2.0f));
	pointLightActor.AddComponent(pointLightTransformComponent);
	std::unique_ptr<ActorComponent> pointLightComponent = std::make_unique<PointLightComponent>(&pointLight);
	pointLightActor.AddComponent(pointLightComponent);
	std::unique_ptr<ActorComponent> pointLightRendererComponent = std::make_unique<SpriteRendererComponent>(graphicsEngine, pointLightSprite);
	pointLightActor.AddComponent(pointLightRendererComponent);

	Actor directionalLightActor("Directional light");

	DirectionalLight directionalLight(glm::vec3(0.05f), glm::vec3(0.4f), glm::vec3(0.5f));

	std::unique_ptr<ActorComponent> directionalLightComponent = std::make_unique<DirectionalLightComponent>(&directionalLight);
	directionalLightActor.AddComponent(directionalLightComponent);

	std::vector<PointLightComponent*> pointLightComponents = {
		pointLightActor.FindComponentByType<PointLightComponent>()
	};

	std::vector<DirectionalLightComponent*> directionalLightComponents = {
		directionalLightActor.FindComponentByType<DirectionalLightComponent>()
	};

	// --- World ---

	Asset* worldAsset = assetManager.CreateBlankAsset(ObjectType(typeid(World)), "Default");
	World* world = (World*)worldAsset->GetObject();

	world->SpawnActor(skyboxActor);
	world->SpawnActor(backpackActor);
	world->SpawnActor(testActor);
	world->SpawnActor(cubeActor);
	world->SpawnActor(suzanneActor);
	world->SpawnActor(pointLightActor);
	world->SpawnActor(directionalLightActor);

	gameManager.LoadWorld(*world);

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
	std::unique_ptr<GlobalData> matricesGlobalData = graphicsEngine.CreateGlobalData("ubo_matrices");
	graphicsEngine.AddDataReferenceToGlobalData(*matricesGlobalData, "view", viewTransform);
	graphicsEngine.AddDataReferenceToGlobalData(*matricesGlobalData, "skybox", skyboxTransform);
	graphicsEngine.AddDataReferenceToGlobalData(*matricesGlobalData, "projection", projectionTransform);

	/* Here, we bind the corresponding uniform block of each of our shaders to the matrices UBO. */
	phongShader->BindToGlobalData(*matricesGlobalData);
	reflectionShader->BindToGlobalData(*matricesGlobalData);
	refractionShader->BindToGlobalData(*matricesGlobalData);
	skyboxShader->BindToGlobalData(*matricesGlobalData);
	spriteShader->BindToGlobalData(*matricesGlobalData);

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
	std::unique_ptr<GlobalData> directionalLightsGlobalData = graphicsEngine.CreateGlobalData("ubo_directionalLights");
	graphicsEngine.AddDataReferenceToGlobalData(*directionalLightsGlobalData, "directionalLight1", directionalLight);
	std::unique_ptr<GlobalData> pointLightsGlobalData = graphicsEngine.CreateGlobalData("ubo_pointLights");
	graphicsEngine.AddDataReferenceToGlobalData(*pointLightsGlobalData, "pointLight1", pointLight);

	phongShader->BindToGlobalData(*directionalLightsGlobalData);
	phongShader->BindToGlobalData(*pointLightsGlobalData);

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
	std::unique_ptr<GlobalData> cameraGlobalData = graphicsEngine.CreateGlobalData("ubo_camera");
	graphicsEngine.AddDataReferenceToGlobalData(*cameraGlobalData, "camera", cameraPosition);

	phongShader->BindToGlobalData(*cameraGlobalData);
	reflectionShader->BindToGlobalData(*cameraGlobalData);
	refractionShader->BindToGlobalData(*cameraGlobalData);

	ImGuiMain ui(applicationManager, assetManager, gameManager, graphicsEngine);

	// This is the render loop.
	while (!glfwWindowShouldClose(window))
	{
		// --- Pre-frame stuff ---

		// Update deltaTime and lastFrame.
		float currentFrame = (float)glfwGetTime();
		g_DeltaTime = currentFrame - g_LastFrameTime;
		g_LastFrameTime = currentFrame;

		/* Checks if any events are triggered (e.g., keyboard input, mouse mouvement),
		updates the window state and calls the corresponding functions. */
		glfwPollEvents();

		ProcessInput(window);

		if (g_CameraMode)
		{
			/* Tell GLFW that it should hide the cursor and capture it. Capturing a cursor
			means that, once the application has focus, the mouse cursor stays within the
			center of the window (unless the application loses focus or quits). */
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		NewImGuiFrame();

		graphicsEngine.StartFrame();

		// --- View and projection transformation matrices ---

		/* Here, we update our matrices UBO data with the new matrices' data. */
		viewTransform = g_Camera.GetViewMatrix();
		skyboxTransform = g_Camera.GetSkyboxMatrix();
		projectionTransform = g_Camera.GetProjectionMatrix();
		matricesGlobalData->SendToDevice();

		/* Here, we update our camera UBO data with the new camera's data. */
		cameraPosition = g_Camera.GetPosition();
		cameraGlobalData->SendToDevice();

		/* Here, we update our lights UBO data with the new lights' data. */
		directionalLightsGlobalData->SendToDevice();
		pointLightsGlobalData->SendToDevice();

		// --- Draw actors ---

		backpackActor.Render();
		cubeActor.Render();
		testActor.Render();
		suzanneActor.Render();
		/* We could've render the skybox first, but we would render fragments that might be overridden
		by the rest of the scene. Knowing that, we render it last and by exploiting depth testing - see
		comments in the skybox vertex shader -, still make it look like it's behind everything. Plus,
		using this neat little trick, we don't have to call glDepthMask with GL_FALSE before rendering the
		skybox and then call it again with GL_TRUE. */
		skyboxActor.Render();
		/* We need to render the actors with transparency last. */
		pointLightActor.Render();

		graphicsEngine.EndFrame();

		ui.Render();

		// --- Post-frame stuff ---

		RenderImGuiFrame();

		/* Rendering applications often have two buffers: the back and the front buffers.
		The front buffer is what is currently displayed in the viewport and the back buffer
		is used to render the current frame. When the render is done, we display the result
		by swapping the front buffer content with the back buffer content. This prevents
		artifacts like flickering, screen tearing and so on. */
		glfwSwapBuffers(window);
	}

	ShutdownImGui();

	glfwTerminate();

	return 0;
}

void InitImGui(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void NewImGuiFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void RenderImGuiFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ShutdownImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
