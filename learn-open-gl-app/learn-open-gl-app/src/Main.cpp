#include <iostream>

#include "Shader.h"
#include "Camera.h"
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

const char* vertexShaderPath = "./shaders/default.vs";
const char* fragmentShaderPath = "./shaders/default.fs";
const char* lightVertexShaderPath = "./shaders/light.vs";
const char* lightFragmentShaderPath = "./shaders/light.fs";
const char* containerTexturePath = "./images/container.jpg";

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;	// Time between current frame and last frame.
float lastFrame = 0.0f;

// Objects
glm::vec3 cubePosition(0.0f, 0.0f, 0.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 lightPosition(1.2f, 1.0f, 2.0f);

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// The OpenGL viewport is relative to the lower left corner of the window.
	glViewport(0, 0, width, height);
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

	/* A vertex is a collection of data per 3D coordinate. We can put anything in our
	vertices. */
	/* Note that our coordinates are all between -1 and 1, which is called the
	Normalized Device Coordinates (NDC). Any values outside this range will not be visible
	in the viewport. Unlike usual screen coordinates, the positive y-axis points in the up-direction
	and the (0, 0) coordinates are at the center of the viewport. */
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	/* Our goal is to draw a rectangle, which is formed of two triangles. The following
	array indicates which vertices form which triangle and in what order OpenGL needs to
	draw them. */
	/* Note that we could've added more vertices in our vertices array to form the
	rectangle, but we would've needed to duplicate the bottom right and top left vertices
	twice each, which is an overhead of 50% (a rectangle requires only 4 vertices). */
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// --- Cube VAO ---

	/* We create a Vertex Array Object (VAO). Any subsequent vertex attribute calls
	from that point on will be stored inside the VAO (including the VBAs associated
	with the vertex attributes based on the calls). Also, the last call to
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ...), which is used to bind an EBO,
	is stored in the VAO. We can simply bind the VAO to automatically bind the VBO,
	make the EBO binding call and all the vertex attribute calls. */
	/* Note that usually, when you have multiple object to draw, you first generate and
	configurate all the VAOs (and thus the required VBO, EBO and attribute pointers) and
	store those for later use. */
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	/* We create a Vertex Buffer Object (VBO) that contains all the vertices that we
	want to send to the GPU's memory for fast access. */
	/* Note that sending data to the GPU from the CPU is slow, so we want to send as much
	data as possible at once. */
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	/* The following function is targeted to copy user-defined data into the currently
	bound buffer. */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* Here, we indicate how OpenGL should interpret the vertex data. */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	/* Here, we create the Element Buffer Object (EBO) that contains the order, using the
	vertices' index, in which OpenGL should draw our triangles. */
	/* Once again, sending data to the GPU from the CPU is slow, so we want to send as much
	data as possible at once. */
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	int width, height, channelCount;
	unsigned char* data;
	/* OpenGL expects the 0.0 coordinate on the y-axis to be on the bottom side of the image,
	but images usually have 0.0 at the top of the y-axis. */
	stbi_set_flip_vertically_on_load(true);

	/* Here, we create a texture. */
	unsigned int texture1;
	glGenTextures(1, &texture1);
	/* We bind our texture so any subsequent texture commands will configure the currently
	bound texture. */
	glBindTexture(GL_TEXTURE_2D, texture1);

	/* Here, we load an image from a file. */
	data = stbi_load(containerTexturePath, &width, &height, &channelCount, 0);
	if (data) {
		/* We assign the loaded image's data to the currently bound texture. */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	/* All the configuration made until this point should be between bind/unbind calls. */
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/* Note that the VAO stores the last glBindBuffer call when the target is
	GL_ELEMENT_ARRAY_BUFFER, which means it stores the unbind calls too (i.e., we call
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) to unbind the EBO). That said, it's important
	to unbind the VAO before the EBO. Otherwise, when we later bind the VAO,
	the VAO's EBO binding call is corresponding to glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0),
	leading to an unconfigured EBO. */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// --- Light VAO ---

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	/* We should use the cube's VBO since the data is already sent to the GPU. Reusing
	the same VBO is more efficient, even if its vertices contains data that is not needed
	for the light, because we avoid having to send and store the data twice. */
	unsigned int lightVBO;
	glGenBuffers(1, &lightVBO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// --- Default shader ---

	Shader defaultShader(vertexShaderPath, fragmentShaderPath);

	/* Even if we activate the texture units (in the render loop), OpenGL doesn't
	know which sampler should be associated to which texture unit. */
	defaultShader.use();
	defaultShader.setInt("texture1", 0);
	defaultShader.setFloatVec3("lightColor1", lightColor);
	defaultShader.setFloatVec3("lightPosition1", lightPosition);

	// --- Light shader ---

	Shader lightShader(lightVertexShaderPath, lightFragmentShaderPath);

	lightShader.use();
	lightShader.setFloatVec3("lightColor", lightColor);

	// --- Cube model transformation matrix ---

	/* Here, we create our model transformation matrix. This will allows us to transform the
	model vertices which are in local space coordinates into world space coordinates. */
	/* Note that the actual transformation order should be read in reverse: even though in
	code we first translate and then later rotate, the actual transformations first apply
	a rotation and then a translation. The recommended order is: scaling, rotation and then
	translation. Otherwise, the transformations would affect each other in unexpected ways, like
	the translation being scaled. */
	/* Note that glm::value_ptr call is important since glm may store the data
	in a way that doesn't always match OpenGL's expectations. */
	glm::mat4 cubeModelTransform = glm::mat4(1.0f);
	cubeModelTransform = glm::translate(cubeModelTransform, cubePosition);
	cubeModelTransform = glm::rotate(cubeModelTransform, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	cubeModelTransform = glm::scale(cubeModelTransform, glm::vec3(1.0f, 5.0f, 1.0f));

	// --- Cube normal transformation matrix ---

	/* Here, we create our normal transformation matrix. Since our normals are hard-coded
	data within the vertices data, we need to transform the normals if we apply a scaling or rotation
	transformation on the cube. */
	/* Note that we don't care about the translation, since normals are directions. That's why we
	convert the 4x4 matrix into a 3x3 matrix -- to remove the translation. */
	/* Note that if we apply a non-uniform scaling transformation, the normals may not be
	perpendicular to the surface anymore. We then inverse then transpose the model matrix
	that our normal transformation matrix is based on. */
	/* See https://learnopengl.com/Lighting/Basic-Lighting for more details. */
	glm::mat3 cubeNormalTransform = glm::mat3(glm::transpose(glm::inverse(cubeModelTransform)));

	// --- Light model transformation matrix ---

	glm::mat4 lightModelTransform = glm::mat4(1.0f);
	lightModelTransform = glm::translate(lightModelTransform, lightPosition);
	lightModelTransform = glm::scale(lightModelTransform, glm::vec3(0.2f));

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

		/* Here, we crate our (perspective) projection transformation matrix. This will allow us to
		project our 3D space coordinates to a 2D space coordinates (i.e., from view space to clip space). */
		glm::mat4 projectionTransform = glm::perspective(glm::radians(camera.fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		// --- Cube drawing ---

		defaultShader.use();
		/* We set the model, view, projection and normal transformation matrices' uniform. This
		is done in the render loop since it tends to change a lot (e.g., when the camera moves). */
		defaultShader.setFloatMat4("model", cubeModelTransform);
		defaultShader.setFloatMat4("view", viewTransform);
		defaultShader.setFloatMat4("projection", projectionTransform);
		defaultShader.setFloatMat3("normalXform", cubeNormalTransform);
		defaultShader.setFloatVec3("cameraPosition", camera.position);

		/* It's a good practice to always activate the texture unit before binding the
		texture. Some drivers will use 0 as the default texture unit, but other drivers
		may not. */
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// --- Light drawing ---

		lightShader.use();
		lightShader.setFloatMat4("model", lightModelTransform);
		lightShader.setFloatMat4("view", viewTransform);
		lightShader.setFloatMat4("projection", projectionTransform);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

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
