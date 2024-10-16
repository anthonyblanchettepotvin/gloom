#pragma once

#include "../ImGuiAdapter.h"

class TransformComponent;

class ImGuiTransformComponentAdapter : public ImGuiAdapter
{
public:
	ImGuiTransformComponentAdapter(TransformComponent& transformComponent);

	void Render() override;

private:
	TransformComponent& m_TransformComponent;
};
