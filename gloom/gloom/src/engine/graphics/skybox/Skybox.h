#pragma once

#include "../../object/Object.h"

class Material;

class Skybox : public Object
{
public:
	Skybox(Material* material);

	Material* GetMaterial() { return m_Material; }

protected:
	Material* m_Material;
};
