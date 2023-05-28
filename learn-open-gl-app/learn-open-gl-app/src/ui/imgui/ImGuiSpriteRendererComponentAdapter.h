#pragma once

#include "../UiComponentAdapter.h"

#include "../../game/component/SpriteRendererComponent.h"

class ImGuiSpriteRendererComponentAdapter : public UiComponentAdapter
{
public:
	ImGuiSpriteRendererComponentAdapter(SpriteRendererComponent* component);

	void RenderUi() const override;
};
