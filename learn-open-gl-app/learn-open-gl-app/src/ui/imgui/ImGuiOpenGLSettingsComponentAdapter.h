#pragma once

#include "../UiComponentAdapter.h"

#include "../../game/component/OpenGLSettingsComponent.h"

class ImGuiOpenGLSettingsComponentAdapter : public UiComponentAdapter
{
public:
	ImGuiOpenGLSettingsComponentAdapter(OpenGLSettingsComponent* component);

	void RenderUi() const override;
};
