#pragma once

#include "../ImGuiAdapter.h"

class PointLightComponent;

class ImGuiPointLightComponentAdapter : public ImGuiAdapter
{
public:
	ImGuiPointLightComponentAdapter(PointLightComponent& pointLightComponent);

	void Render() override;

private:
	PointLightComponent& m_PointLightComponent;
};
