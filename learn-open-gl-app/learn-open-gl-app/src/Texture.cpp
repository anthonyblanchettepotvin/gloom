#include "Texture.h"

#include "stb_image.h" // Image loading library by Sean Barrett.

#include <iostream>

Texture::Texture(const std::string& path, const std::string& type, bool flipVerticallyOnLoad)
	: path(path), type(type)
{
	/* OpenGL expects the 0.0 coordinate on the y-axis to be on the bottom side of the image,
	but images usually have 0.0 at the top of the y-axis. */
	stbi_set_flip_vertically_on_load(flipVerticallyOnLoad);

	/* Here, we create a texture. */
	glGenTextures(1, &id);
	/* We bind our texture so any subsequent texture commands will configure the currently
	bound texture. */
	glBindTexture(GL_TEXTURE_2D, id);

	int width, height, channelCount;

	/* Here, we load an image from a file. */
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channelCount, 0);
	if (data) {
		/* We assign the loaded image's data to the currently bound texture. */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	/* We unbind our texture. */
	glBindTexture(GL_TEXTURE_2D, 0);
}
