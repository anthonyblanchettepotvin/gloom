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
		GLenum format;
		if (channelCount == 1)
			format = GL_RED;
		else if (channelCount == 3)
			format = GL_RGB;
		else if (channelCount == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, id);
		/* We assign the loaded image's data to the currently bound texture. */
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		std::cout << "ERROR::TEXTURE::LOADING::" << path << std::endl;
	}

	stbi_image_free(data);

	/* We unbind our texture. */
	glBindTexture(GL_TEXTURE_2D, 0);
}
