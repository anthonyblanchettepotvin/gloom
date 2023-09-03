#pragma once

#include "../ImGuiAdapter.h"

class Cubemap;
class ImGuiAdapterFactory;

class ImGuiCubemapAdapter : public ImGuiAdapter
{
public:
	ImGuiCubemapAdapter(ImGuiAdapterFactory& adapterFactory, Cubemap& cubemap);

	void Render() override;

private:
	ImGuiAdapterFactory& m_AdapterFactory;

	Cubemap& m_Cubemap;
};
