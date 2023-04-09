#pragma once

#include "../UiComponentAdapter.h"

#include "../../components/OpenGLSettingsComponent.h"

class ImGuiOpenGLSettingsComponentAdapter : public UiComponentAdapter
{
public:
	ImGuiOpenGLSettingsComponentAdapter(OpenGLSettingsComponent* component);

	void RenderUi() const override;
};
