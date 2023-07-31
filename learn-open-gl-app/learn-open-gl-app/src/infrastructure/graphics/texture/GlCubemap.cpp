#include "GlCubemap.h"

#include "glad/glad.h"

#include "GlCubemapTexture.h"

GlCubemap::GlCubemap(const std::vector<CubemapTexture*>& textures)
	: Cubemap(textures), m_Index(0)
{
	glGenTextures(1, &m_Id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);

	for (size_t i = 0; i < textures.size(); i++)
	{
		if (GlCubemapTexture* glTexture = dynamic_cast<GlCubemapTexture*>(textures[i]))
		{
			glTexture->Register(i);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void GlCubemap::Use(unsigned int index)
{
	m_Index = index;

	glActiveTexture(GL_TEXTURE0 + m_Index);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);
}

void GlCubemap::Free()
{
	glActiveTexture(GL_TEXTURE0 + m_Index);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
