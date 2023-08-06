#pragma once

#include "../../engine/GraphicsEngine.h"
#include "../../material/Material.h"
#include "../RenderingPrimitive.h"

class Skybox : public RenderingPrimitive
{
public:
	Skybox(Material* material);

	void Render(GraphicsEngine& graphicsEngine);

	Material* GetMaterial() const { return m_Material; }

protected:
	Material* m_Material;
};
