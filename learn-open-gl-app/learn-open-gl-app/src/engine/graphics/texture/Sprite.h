#pragma once

#include "Texture.h"

#include "../shader/Shader.h"

class Sprite
{
public:
	Sprite(Texture* texture);

	Texture* GetTexture() { return texture; };

	void Render(Shader* shader);

private:
	Texture* texture;

	unsigned int VAO;
	unsigned int VBO;

	void SetupMesh();
};
