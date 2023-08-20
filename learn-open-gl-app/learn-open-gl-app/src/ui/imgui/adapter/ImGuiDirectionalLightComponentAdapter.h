#pragma once

#include "../ImGuiAdapter.h"

class DirectionalLightComponent;

class ImGuiDirectionalLightComponentAdapter : public ImGuiAdapter
{
public:
	ImGuiDirectionalLightComponentAdapter(DirectionalLightComponent& directionalLightComponent);

	void Render() const override;

private:
	DirectionalLightComponent& m_DirectionalLightComponent;
};
