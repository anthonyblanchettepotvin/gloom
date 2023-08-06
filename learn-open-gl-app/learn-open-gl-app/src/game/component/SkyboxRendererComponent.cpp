#include "SkyboxRendererComponent.h"

SkyboxRendererComponent::SkyboxRendererComponent(Skybox* skybox)
	: m_Skybox(skybox)
{
}

void SkyboxRendererComponent::Render()
{
	if (m_Skybox)
	{
		m_Skybox->Render();
	}
}
