#include "SkyboxRendererComponent.h"

SkyboxRendererComponent::SkyboxRendererComponent(GraphicsEngine& graphicsEngine, Skybox* skybox)
	: RendererComponent(graphicsEngine), m_Skybox(skybox)
{
}

void SkyboxRendererComponent::Render()
{
	if (m_Skybox)
	{
		m_Skybox->Render(m_GraphicsEngine);
	}
}
