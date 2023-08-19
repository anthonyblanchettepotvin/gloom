#pragma once

#include "ImGuiAdapter.h"

class Cubemap;
class ImGuiAdapterFactory;

class ImGuiCubemapAdapter : public ImGuiAdapter
{
public:
	ImGuiCubemapAdapter(const ImGuiAdapterFactory& adapterFactory, Cubemap& cubemap);

	void Render() const override;

private:
	const ImGuiAdapterFactory& m_AdapterFactory;

	Cubemap& m_Cubemap;
};
