#pragma once

#include "Texture.h"

#include "../shader/Shader.h"

class Sprite
{
public:
	Sprite(Texture* texture);

	Texture* GetTexture() { return texture; };

	virtual void Render(Shader* shader) = 0;

protected:
	Texture* texture;
};
