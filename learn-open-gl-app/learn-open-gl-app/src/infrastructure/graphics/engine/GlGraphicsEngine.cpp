#include "GlGraphicsEngine.h"

#include "../globaldata/GlGlobalData.h"
#include "../globaldata/GlGlobalDataTypes.h"

GlobalData* GlGraphicsEngine::CreateGlobalData(const std::string& name)
{
	return new GlGlobalData(name);
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(const std::string& name, float& reference, GlobalData* globalData)
{
	if (GlGlobalData* glGlobalData = dynamic_cast<GlGlobalData*>(globalData))
	{
		GlGlobalDataFloat* glReference = new GlGlobalDataFloat(reference);
		glGlobalData->AddDataReference(name, *glReference);
	}
	else
	{
		// TODO: Throw bad global data type exception
	}
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(const std::string& name, glm::mat4& reference, GlobalData* globalData)
{
	if (GlGlobalData* glGlobalData = dynamic_cast<GlGlobalData*>(globalData))
	{
		GlGlobalDataMat4* glReference = new GlGlobalDataMat4(reference);
		glGlobalData->AddDataReference(name, *glReference);
	}
	else
	{
		// TODO: Throw bad global data type exception
	}
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(const std::string& name, glm::vec3& reference, GlobalData* globalData)
{
	if (GlGlobalData* glGlobalData = dynamic_cast<GlGlobalData*>(globalData))
	{
		GlGlobalDataVec3* glReference = new GlGlobalDataVec3(reference);
		glGlobalData->AddDataReference(name, *glReference);
	}
	else
	{
		// TODO: Throw bad global data type exception
	}
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(const std::string& name, DirectionalLight& reference, GlobalData* globalData)
{
	if (GlGlobalData* glGlobalData = dynamic_cast<GlGlobalData*>(globalData))
	{
		GlGlobalDataDirectionalLight* glReference = new GlGlobalDataDirectionalLight(reference);
		glGlobalData->AddDataReference(name, *glReference);
	}
	else
	{
		// TODO: Throw bad global data type exception
	}
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(const std::string& name, PointLight& reference, GlobalData* globalData)
{
	if (GlGlobalData* glGlobalData = dynamic_cast<GlGlobalData*>(globalData))
	{
		GlGlobalDataPointLight* glReference = new GlGlobalDataPointLight(reference);
		glGlobalData->AddDataReference(name, *glReference);
	}
	else
	{
		// TODO: Throw bad global data type exception
	}
}
