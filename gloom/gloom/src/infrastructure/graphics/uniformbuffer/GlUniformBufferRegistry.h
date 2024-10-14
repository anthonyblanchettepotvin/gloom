#pragma once

#include <string>
#include <memory>
#include <vector>

#include "GlUniformBuffer.h"

class GlUniformBufferRegistry // TODO: Eliminate code duplication with AssetRepository.
{
public:
	void Insert(std::unique_ptr<GlUniformBuffer>& uniformBuffer);

	GlUniformBuffer* FindUniformBufferByName(const std::string& uniformBufferName);
	const GlUniformBuffer* FindUniformBufferByName(const std::string& uniformBufferName) const;

	std::vector<GlUniformBuffer*> GetUniformBuffers();
	std::vector<const GlUniformBuffer*> GetUniformBuffers() const;

private:
	std::vector<std::unique_ptr<GlUniformBuffer>> m_UniformBuffers;

	template<class T, class Self>
	friend T* FindUniformBufferByNameImpl(Self& self, const std::string& uniformBufferName);

	template<class T, class Self>
	friend std::vector<T*> GetUniformBuffersImpl(Self& self);
};
