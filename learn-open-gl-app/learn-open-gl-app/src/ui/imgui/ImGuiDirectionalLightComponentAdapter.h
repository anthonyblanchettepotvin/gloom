#pragma once

#include "../UiComponentAdapter.h"

#include "../../components/DirectionalLightComponent.h"

class ImGuiDirectionalLightComponentAdapter : public UiComponentAdapter
{
public:
	ImGuiDirectionalLightComponentAdapter(DirectionalLightComponent* component);

	void RenderUi() const override;
};
