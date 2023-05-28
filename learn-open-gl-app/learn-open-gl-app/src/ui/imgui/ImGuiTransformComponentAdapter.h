#pragma once

#include "../UiComponentAdapter.h"

#include "../../game/component/TransformComponent.h"

class ImGuiTransformComponentAdapter : public UiComponentAdapter
{
public:
	ImGuiTransformComponentAdapter(TransformComponent* component);

	void RenderUi() const override;
};
