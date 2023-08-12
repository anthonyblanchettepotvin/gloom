#pragma once

#include "../../object/Object.h"

#include "../material/Material.h"

class Skybox : public Object<Skybox>
{
public:
	Skybox(Material* material);

	Material* GetMaterial() const { return m_Material; }

protected:
	Material* m_Material;
};
