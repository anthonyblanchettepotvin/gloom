#include "GlGlobalDataTypes.h"

GlGlobalDataMat4::GlGlobalDataMat4(glm::mat4& value)
	: value(value)
{
}

unsigned int GlGlobalDataMat4::GetBaseAlignment()
{
	return 16;
}

unsigned int GlGlobalDataMat4::GetSize()
{
	return sizeof(glm::mat4);
}

void* GlGlobalDataMat4::GetValuePointer()
{
	return (void*) &value;
}
