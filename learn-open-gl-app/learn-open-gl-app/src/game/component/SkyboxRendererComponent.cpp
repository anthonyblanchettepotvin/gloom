#include "SkyboxRendererComponent.h"

SkyboxRendererComponent::SkyboxRendererComponent(Skybox* skybox, Shader* shader)
	: RendererComponent(shader), skybox(skybox)
{
}

void SkyboxRendererComponent::Render()
{
	if (shader && skybox)
	{
		shader->Use();

		skybox->Render(shader);
	}
}
