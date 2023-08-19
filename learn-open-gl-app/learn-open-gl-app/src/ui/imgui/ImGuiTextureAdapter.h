#pragma once

#include "ImGuiAdapter.h"

class GraphicsEngine;
class ImVec2;
class Texture;

class ImGuiTextureAdapter : public ImGuiAdapter
{
public:
	ImGuiTextureAdapter(Texture& texture, GraphicsEngine& graphicsEngine);

	void Render() const override;

private:
	Texture& m_Texture;

	GraphicsEngine& m_GraphicsEngine;

	ImVec2 GetTexturePreviewUvStart() const;
	ImVec2 GetTexturePreviewUvEnd() const;
};
