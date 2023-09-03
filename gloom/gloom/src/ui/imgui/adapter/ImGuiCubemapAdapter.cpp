#include "ImGuiCubemapAdapter.h"

#include <memory>

#include "../../../vendor/imgui/imgui.h"

#include "../../../engine/graphics/cubemap/Cubemap.h"
#include "../../../engine/graphics/texture/Texture.h"

#include "../ImGuiAdapterFactory.h"

ImGuiCubemapAdapter::ImGuiCubemapAdapter(ImGuiAdapterFactory& adapterFactory, Cubemap& cubemap)
	: m_AdapterFactory(adapterFactory), m_Cubemap(cubemap)
{
}

void ImGuiCubemapAdapter::Render()
{
	for (const auto& texture : m_Cubemap.GetTextures())
	{
		std::unique_ptr<ImGuiAdapter> textureAdapter = m_AdapterFactory.CreateAdapter(texture);
		if (textureAdapter)
		{
			textureAdapter->Render();
		}
	}
}
