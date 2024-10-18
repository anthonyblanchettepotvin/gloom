#pragma once

#include "../ImGuiAdapter.h"

class Shader;

class ImGuiShaderAdapter : public ImGuiAdapter
{
public:
	ImGuiShaderAdapter(Shader& shader);

	void Render() override;

private:
	Shader& m_Shader;
};
