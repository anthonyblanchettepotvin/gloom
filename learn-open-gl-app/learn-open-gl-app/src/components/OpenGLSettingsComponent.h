#pragma once

#include "ActorComponent.h"

enum class OpenGLDepthFunction {
	ALWAYS,
	NEVER,
	LESS,
	EQUAL,
	LEQUAL,
	GREATER,
	NOTEQUAL,
	GEQUAL,
	COUNT
};

class OpenGLSettingsComponent : public ActorComponent
{
public:
	bool& GetDepthTestingEnabledReference() { return depthTestingEnabled; }

	OpenGLDepthFunction& GetDepthFunctionReference() { return depthFunction; }

private:
	bool depthTestingEnabled = true;

	OpenGLDepthFunction depthFunction = OpenGLDepthFunction::LESS;
};
