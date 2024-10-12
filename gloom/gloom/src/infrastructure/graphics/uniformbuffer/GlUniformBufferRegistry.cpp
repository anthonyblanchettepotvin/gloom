#include "GlUniformBufferRegistry.h"

#include <cassert>
#include <stdexcept>

#include "../../../engine/EngineHelpers.h"

#include "GlUniformBuffer.h"

#define ASSET_ALREADY_IN_REPOSITORY "Uniform buffer is already in the repository."

void GlUniformBufferRegistry::Insert(std::unique_ptr<GlUniformBuffer>& uniformBuffer)
{
	// TODO: Uniform buffer name should be unique.

	if (!uniformBuffer)
	{
		throw std::invalid_argument(ARGUMENT_IS_NULLPTR(uniformBuffer));
	}

	auto it = std::find(m_UniformBuffers.begin(), m_UniformBuffers.end(), uniformBuffer);
	if (it != m_UniformBuffers.end())
	{
		throw std::runtime_error(ASSET_ALREADY_IN_REPOSITORY);
	}

	m_UniformBuffers.emplace_back(std::move(uniformBuffer));
}

template<class T, class Self>
T* FindUniformBufferByNameImpl(Self& self, const std::string& uniformBufferName)
{
	for (const auto& uniformBuffer : self.m_UniformBuffers)
	{
		assert(uniformBuffer != nullptr);

		if (uniformBuffer->GetName() == uniformBufferName)
		{
			return uniformBuffer.get();
		}
	}

	return nullptr;
}

GlUniformBuffer* GlUniformBufferRegistry::FindUniformBufferByName(const std::string& uniformBufferName)
{
	return FindUniformBufferByNameImpl<GlUniformBuffer>(*this, uniformBufferName);
}

const GlUniformBuffer* GlUniformBufferRegistry::FindUniformBufferByName(const std::string& uniformBufferName) const
{
	return FindUniformBufferByNameImpl<const GlUniformBuffer>(*this, uniformBufferName);
}

template<class T, class Self>
std::vector<T*> GetUniformBuffersImpl(Self& self)
{
	std::vector<T*> result;

	for (const auto& uniformBuffer : self.m_UniformBuffers)
	{
		assert(uniformBuffer != nullptr);

		result.push_back(uniformBuffer.get());
	}

	return result;
}

std::vector<GlUniformBuffer*> GlUniformBufferRegistry::GetUniformBuffers()
{
	return GetUniformBuffersImpl<GlUniformBuffer>(*this);
}

std::vector<const GlUniformBuffer*> GlUniformBufferRegistry::GetUniformBuffers() const
{
	return GetUniformBuffersImpl<const GlUniformBuffer>(*this);
}
