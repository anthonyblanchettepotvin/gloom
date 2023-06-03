#pragma once

#include <glm/glm.hpp>

#include "GlGlobalDataType.h"

class GlGlobalDataMat4 : public GlGlobalDataType
{
public:
	GlGlobalDataMat4(glm::mat4& value);

	unsigned int GetBaseAlignment() override;
	unsigned int GetSize() override;

	void* GetValuePointer() override;

private:
	glm::mat4& value;
};
