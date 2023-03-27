#include <iostream>

#include "Shader.h"
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

const char* vertexShaderPath = "./shaders/default.vs";
const char* fragmentShaderPath = "./shaders/default.fs";

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// The OpenGL viewport is relative to the lower left corner of the window.
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// The following instruction is required on macOS.
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
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

	/* A vertex is a collection of data per 3D coordinate. We can put anything in our
	vertices. Here, we have a position attribute (3 first floats/line) and a color attribute
	(3 last floats/line). */
	/* Note that our coordinates are all between -1 and 1, which is called the
	Normalized Device Coordinates (NDC). Any values outside this range will not be visible
	in the viewport. */
	/* Unlike usual screen coordinates, the positive y-axis points in the up-direction
	and the (0, 0) coordinates are at the center of the viewport. */
	float vertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
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

	/* Here, we indicate how OpenGL should interpret the vertex data. In our case,
	each vertex is composed of a 3D position, a RGB color and texture coordiates.
	So, each vertex has 3 floats of 4 bytes for the 3D position, 3 floats of 4 bytes
	for the color and 2 floats of 4 bytes for the texture coordinates. So, each vertex
	has a stride of 32 bytes. */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/* Note that the color attribute is placed after the position attribute, so
	we need an offset of 12 bytes. */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	/* Note that the texture coordinates attribute is placed after the color attribute, so
	we need an offset of 24 bytes. */
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

	/* Here, we create a first texture. */
	unsigned int texture1;
	glGenTextures(1, &texture1);
	/* We bind our texture so any subsequent texture commands will configure the currently
	bound texture. */
	glBindTexture(GL_TEXTURE_2D, texture1);

	/* Here, we load an image from a file. */
	data = stbi_load("./images/container.jpg", &width, &height, &channelCount, 0);
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

	/* Here, we create a second texture. The steps are the same as the previous one. */
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	data = stbi_load("./images/awesomeface.png", &width, &height, &channelCount, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	/* All the configuration made until this point should between bind/unbind calls. */
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/* Note that the VAO stores the last glBindBuffer call when the target is
	GL_ELEMENT_ARRAY_BUFFER, which means it stores the unbind calls too (i.e., we call
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) to unbind the EBO). That said, it's important
	to unbind the VAO before the EBO. Otherwise, when we later bind the VAO,
	the VAO's EBO binding call is corresponding to glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0),
	leading to an unconfigured EBO. */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	Shader defaultShader(vertexShaderPath, fragmentShaderPath);

	/* Even if we activate the shader position 0 and 1 (in the render loop), OpenGL doesn't
	know which sampler should be associated to which texture unit. */
	defaultShader.use();
	defaultShader.setInt("texture1", 0);
	defaultShader.setInt("texture2", 1);

	// This is the render loop.
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		defaultShader.use();
		/* It's a good practice to always activate the texture unit before binding the
		texture. Some drivers will use 0 as the default texture unit, but other drivers
		may not. */
		// We assign the first texture to the unit 0.
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		// We assign the second texture to the unit 1.
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

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
