#pragma once

#include "../../material/Material.h"

class Skybox
{
public:
	Skybox(Material* material);

	Material* GetMaterial() const { return m_Material; }

protected:
	Material* m_Material;
};
