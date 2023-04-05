#pragma once

#include "../UiComponentAdapter.h"

#include "../../components/ModelRendererComponent.h"

class ImGuiModelRendererComponentAdapter : public UiComponentAdapter
{
public:
	ImGuiModelRendererComponentAdapter(ModelRendererComponent* component);

	void RenderUi() const override;
};
