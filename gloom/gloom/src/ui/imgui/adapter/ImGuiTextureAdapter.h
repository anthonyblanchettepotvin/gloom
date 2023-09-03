#pragma once

#include "../ImGuiAdapter.h"

class GraphicsEngine;
class ImVec2;
class Texture;

class ImGuiTextureAdapter : public ImGuiAdapter
{
public:
	ImGuiTextureAdapter(GraphicsEngine& graphicsEngine, Texture& texture);

	void Render() override;

private:
	ImVec2 GetTexturePreviewUvStart() const;
	ImVec2 GetTexturePreviewUvEnd() const;

	GraphicsEngine& m_GraphicsEngine;

	Texture& m_Texture;
};
