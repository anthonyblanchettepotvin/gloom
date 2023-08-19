#include "ImGuiCubemapAdapter.h"

#include "../../vendor/imgui/imgui.h"

#include "../../engine/graphics/cubemap/Cubemap.h"

#include "ImGuiAdapterFactory.h"

ImGuiCubemapAdapter::ImGuiCubemapAdapter(const ImGuiAdapterFactory& adapterFactory, Cubemap& cubemap)
	: m_AdapterFactory(adapterFactory), m_Cubemap(cubemap)
{
}

void ImGuiCubemapAdapter::Render() const
{
	for (const auto& texture : m_Cubemap.GetTextures())
	{
		ImGuiAdapter* textureAdapter = m_AdapterFactory.CreateAdapter(texture);
		if (textureAdapter)
		{
			textureAdapter->Render();
		}
	}
}
