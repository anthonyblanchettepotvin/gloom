#pragma once

#include "../UiComponentAdapter.h"

#include "../../components/PointLightComponent.h"

class ImGuiPointLightComponentAdapter : public UiComponentAdapter
{
public:
	ImGuiPointLightComponentAdapter(PointLightComponent* component);

	void RenderUi() const override;
};
