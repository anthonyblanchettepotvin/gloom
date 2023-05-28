#pragma once

#include "../UiComponentAdapter.h"

#include "../../game/component/DirectionalLightComponent.h"

class ImGuiDirectionalLightComponentAdapter : public UiComponentAdapter
{
public:
	ImGuiDirectionalLightComponentAdapter(DirectionalLightComponent* component);

	void RenderUi() const override;
};
