#include "GlGraphicsEngine.h"

#include "../globaldata/GlGlobalData.h"
#include "../globaldata/GlGlobalDataTypes.h"

GlobalData* GlGraphicsEngine::CreateGlobalData()
{
	return new GlGlobalData();
}

void GlGraphicsEngine::AddDataReferenceToGlobalData(const std::string& name, glm::mat4& reference, GlobalData* globalData)
{
	GlGlobalDataMat4* glReference = new GlGlobalDataMat4(reference);
	if (GlGlobalData* glGlobalData = dynamic_cast<GlGlobalData*>(globalData)) {
		glGlobalData->AddDataReference(name, *glReference);
	}
	else
	{
		//Throw bad global data type
	}
}
