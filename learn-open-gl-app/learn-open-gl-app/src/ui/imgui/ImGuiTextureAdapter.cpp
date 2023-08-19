#include "ImGuiTextureAdapter.h"

#include "../../vendor/imgui/imgui.h"

#include "../../engine/graphics/engine/GraphicsEngine.h"
#include "../../engine/graphics/texture/Texture.h"

#define TEXTURE_PREVIEW_SIZE ImVec2(128, 128)

ImGuiTextureAdapter::ImGuiTextureAdapter(Texture& texture, GraphicsEngine& graphicsEngine)
	: m_Texture(texture), m_GraphicsEngine(graphicsEngine)
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
	ImVec2 uvStart(0, 0);

	if (m_Texture.GetIsFlippedVertically())
		uvStart.y = 1;

	if (m_Texture.GetIsFlippedHorizontally())
		uvStart.x = 1;

	return uvStart;
}

ImVec2 ImGuiTextureAdapter::GetTexturePreviewUvEnd() const
{
	ImVec2 uvEnd(1, 1);

	if (m_Texture.GetIsFlippedVertically())
		uvEnd.y = 0;

	if (m_Texture.GetIsFlippedHorizontally())
		uvEnd.x = 0;

	return uvEnd;
}
