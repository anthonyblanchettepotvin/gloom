#pragma once

#include "../UiComponentAdapter.h"

#include "../../game/component/ModelRendererComponent.h"

class ImGuiModelRendererComponentAdapter : public UiComponentAdapter
{
public:
	ImGuiModelRendererComponentAdapter(ModelRendererComponent* component);

	void RenderUi() const override;
};
