#include <iostream>

#include "engine/graphics/cubemap/Cubemap.h"
#include "engine/graphics/engine/GraphicsEngine.h"
#include "engine/graphics/material/MaterialAttributes.h"
#include "engine/graphics/model/Model.h"
#include "engine/graphics/shader/Shader.h"
#include "engine/graphics/skybox/Skybox.h"
#include "engine/graphics/sprite/Sprite.h"
#include "engine/graphics/texture/Texture.h"
#include "game/actor/Actor.h"
#include "game/asset/shader/ShaderLoader.h"
#include "game/asset/shader/ShaderRegistry.h"
#include "game/camera/Camera.h"
#include "game/component/TransformComponent.h"
#include "game/component/ModelRendererComponent.h"
#include "game/component/SkyboxRendererComponent.h"
#include "game/component/SpriteRendererComponent.h"
#include "game/component/PointLightComponent.h"
#include "game/component/DirectionalLightComponent.h"
#include "game/world/World.h"
#include "infrastructure/graphics/engine/GlGraphicsEngine.h"
#include "infrastructure/graphics/shader/GlShaderLoader.h"
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

const std::string CUBEMAP_FACES_PATH = ".\\images\\nightCubemap";

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
	ImGui::ListBox("Actors", &currentItem, actorsCName.data(), (int)world.GetActors().size());
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
