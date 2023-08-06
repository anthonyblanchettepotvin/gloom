#pragma once

#include "../material/Material.h"

class Skybox
{
public:
	Skybox(Material* material);

	virtual void Render() = 0;

protected:
	Material* m_Material;
};
