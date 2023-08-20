#include "ImGuiTextureAdapter.h"

#include "../../../vendor/imgui/imgui.h"

#include "../../../engine/graphics/engine/GraphicsEngine.h"
#include "../../../engine/graphics/texture/Texture.h"

#define TEXTURE_PREVIEW_SIZE ImVec2(128, 128)

ImGuiTextureAdapter::ImGuiTextureAdapter(GraphicsEngine& graphicsEngine, Texture& texture)
	: m_GraphicsEngine(graphicsEngine), m_Texture(texture)
{
}

void ImGuiTextureAdapter::Render() const
{
	ImGui::Image(m_GraphicsEngine.GetTextureId(m_Texture), TEXTURE_PREVIEW_SIZE, GetTexturePreviewUvStart(), GetTexturePreviewUvEnd());

	int textureWidth = m_Texture.GetWidth();
	ImGui::InputInt("Width", &textureWidth, NULL, NULL, ImGuiInputTextFlags_ReadOnly);

	int textureHeight = m_Texture.GetHeight();
	ImGui::InputInt("Height", &textureHeight, NULL, NULL, ImGuiInputTextFlags_ReadOnly);

	int textureChannelCount = m_Texture.GetChannelCount();
	ImGui::InputInt("Channel Count", &textureChannelCount, NULL, NULL, ImGuiInputTextFlags_ReadOnly);
}

ImVec2 ImGuiTextureAdapter::GetTexturePreviewUvStart() const
{
	ImVec2 texturePreviewUvStart(0, 0);

	if (m_Texture.GetIsFlippedVertically())
	{
		texturePreviewUvStart.y = 1;
	}

	if (m_Texture.GetIsFlippedHorizontally())
	{
		texturePreviewUvStart.x = 1;
	}

	return texturePreviewUvStart;
}

ImVec2 ImGuiTextureAdapter::GetTexturePreviewUvEnd() const
{
	ImVec2 texturePreviewUvEnd(1, 1);

	if (m_Texture.GetIsFlippedVertically())
	{
		texturePreviewUvEnd.y = 0;
	}

	if (m_Texture.GetIsFlippedHorizontally())
	{
		texturePreviewUvEnd.x = 0;
	}

	return texturePreviewUvEnd;
}
