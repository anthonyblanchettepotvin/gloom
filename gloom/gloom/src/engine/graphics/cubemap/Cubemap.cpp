#include "Cubemap.h"

#include <cassert>
#include <stdexcept>

#include "../../EngineHelpers.h"

Cubemap::Cubemap(std::vector<std::unique_ptr<Texture>>& textures)
{
	for (const auto& texture : textures)
	{
		if (!texture)
		{
			throw std::invalid_argument(ARGUMENT_CONTAINS_NULLPTR(textures));
		}
	}

	m_Textures = std::move(textures);
}

template<class T, class Self>
inline std::vector<T*> GetTexturesImpl(Self& self)
{
	std::vector<T*> result;

	for (const auto& texture : self.m_Textures)
	{
		assert(texture != nullptr);

		result.push_back(texture.get());
	}

	return result;
}

std::vector<Texture*> Cubemap::GetTextures()
{
	return GetTexturesImpl<Texture>(*this);
}

std::vector<const Texture*> Cubemap::GetTextures() const
{
	return GetTexturesImpl<const Texture>(*this);
}
