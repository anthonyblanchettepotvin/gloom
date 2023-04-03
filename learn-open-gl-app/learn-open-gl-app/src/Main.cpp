#include <iostream>

#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Model.h"
#include "Actor.h"

#include "stb_image.h" // Image loading library by Sean Barrett.

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

const char* PHONG_VERTEX_SHADER_PATH = "./shaders/phong.vs";
const char* PHONG_FRAGMENT_SHADER_PATH = "./shaders/phong.fs";
const char* POINT_LIGHT_VERTEX_SHADER_PATH = "./shaders/pointLight.vs";
const char* POINT_LIGHT_FRAGMENT_SHADER_PATH = "./shaders/pointLight.fs";

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), SCR_WIDTH, SCR_HEIGHT);

// Mouse
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;	// Time between current frame and last frame.
float lastFrame = 0.0f;

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetScrollCallback(window, scrollCallback);

	// --- Models ---

	Model lightModel("C:\\Users\\Anthony\\Downloads\\backpack\\backpack.obj");
	Model backpackModel("C:\\Users\\Anthony\\Downloads\\backpack\\backpack.obj");

	// --- Shaders ---

	Shader defaultShader(PHONG_VERTEX_SHADER_PATH, PHONG_FRAGMENT_SHADER_PATH);

	defaultShader.use();
	defaultShader.setFloat("material.shininess", 4.0f);

	Shader lightShader(POINT_LIGHT_VERTEX_SHADER_PATH, POINT_LIGHT_FRAGMENT_SHADER_PATH);

	// --- Actors ---

	Actor backpackActor(glm::vec3(0.0f), &backpackModel);

	// --- Lights ---

	std::vector<PointLight> pointLights = {
		PointLight(glm::vec3(1.0f), &lightModel)
	};

	for (size_t i = 0; i < pointLights.size(); i++)
	{
		std::string identifier = "pointLights[" + std::to_string(i) + "]";
		
		pointLights[i].Register(defaultShader, identifier);
	}

	std::vector<DirectionalLight> directionalLights = {
		DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f))
	};

	for (size_t i = 0; i < directionalLights.size(); i++)
	{
		std::string identifier = "directionalLights[" + std::to_string(i) + "]";

		directionalLights[i].Register(defaultShader, identifier);
	}

	/* OpenGL draws your cube triangle-by-triangle, fragment by fragment, it will overwrite any
	pixel color that may have already been drawn there before. Since OpenGL gives no guarantee
	on the order of triangles rendered (within the same draw call), some triangles are drawn
	on top of each other even though one should clearly be in front of the other.*/
	/* Note that if we enable depth testing, we need to clear the depth buffer in each frame. */
	glEnable(GL_DEPTH_TEST);

	// This is the render loop.
	while (!glfwWindowShouldClose(window))
	{
		// --- Pre-frame stuff ---

		// Update deltaTime and lastFrame.
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// --- View and projection transformation matrices ---

		glm::mat4 viewTransform = camera.GetViewMatrix();
		glm::mat4 projectionTransform = camera.GetProjectionMatrix();

		// --- Draw actors ---

		defaultShader.use();
		defaultShader.setFloatMat4("viewXform", viewTransform);
		defaultShader.setFloatMat4("projectionXform", projectionTransform);
		defaultShader.setFloatVec3("camera.position", camera.GetPosition());

		backpackActor.Draw(defaultShader);

		// --- Draw lights ---

		lightShader.use();
		lightShader.setFloatMat4("viewXform", viewTransform);
		lightShader.setFloatMat4("projectionXform", projectionTransform);

		for (size_t i = 0; i < pointLights.size(); i++)
		{
			pointLights[i].Draw(lightShader);
		}

		// --- Post-frame stuff ---

		/* Rendering applications often have two buffers: the back and the front buffers.
		The front buffer is what is currently displayed in the viewport and the back buffer
		is used to render the current frame. When the render is done, we display the result
		by swapping the front buffer content with the back buffer content. This prevents
		artifacts like flickering, screen tearing and so on. */
		glfwSwapBuffers(window);

		/* Checks if any events are triggered (e.g., keyboard input, mouse mouvement),
		updates the window state and calls the corresponding functions. */
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
