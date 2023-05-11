#include "Cubemap.h"

#include <iostream>

#include <glad/glad.h>
#include "stb_image.h"

Cubemap::Cubemap(const std::vector<std::string>& facesPath, bool flipVerticallyOnLoad)
{
	stbi_set_flip_vertically_on_load(flipVerticallyOnLoad);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	for (size_t i = 0; i < facesPath.size(); i++)
	{
		std::string facePath = facesPath.at(i);

		int width, height, channelCount;
		unsigned char* data = stbi_load(facePath.c_str(), &width, &height, &channelCount, 0);
		if (data)
		{
			/* That's a neat little trick here. OpenGL define the six targets (one for each face of the cubemap)
			one after the other in order. We can then iterate over an array and simply offset the
			first target by the iteration to get the value of the current target. */
			/* You can get the list of all the cubemap targets here https://learnopengl.com/Advanced-OpenGL/Cubemaps. */
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			std::cout << "ERROR::CUBEMAP::LOADING::" << facePath << std::endl;
		}

		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
