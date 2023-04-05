#pragma once

#include "../UiComponentAdapter.h"

#include "../../components/SpriteRendererComponent.h"

class ImGuiSpriteRendererComponentAdapter : public UiComponentAdapter
{
public:
	ImGuiSpriteRendererComponentAdapter(SpriteRendererComponent* component);

	void RenderUi() const override;
};
