#include "SkyboxRendererComponent.h"

SkyboxRendererComponent::SkyboxRendererComponent(GraphicsEngine& graphicsEngine, Skybox* skybox)
	: RendererComponent(graphicsEngine), m_Skybox(skybox)
{
}

void SkyboxRendererComponent::Render()
{
	if (m_Skybox)
	{
		if (!m_GraphicsObject)
		{
			m_GraphicsObject = m_GraphicsEngine.CreateGraphicsObject(*m_Skybox);
		}

		m_GraphicsObject->Render();
	}
}
