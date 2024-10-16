#include "SkyboxRendererComponent.h"

#include "../../engine/graphics/engine/GraphicsEngine.h"
#include "../../engine/graphics/skybox/Skybox.h"

SkyboxRendererComponent::SkyboxRendererComponent(GraphicsEngine& graphicsEngine, Skybox* skybox)
	: RendererComponent(graphicsEngine), m_Skybox(skybox)
{
}

void SkyboxRendererComponent::Render(const Camera& camera)
{
	if (!m_Skybox)
	{
		return;
	}

	m_GraphicsEngine.Render(camera, *m_Skybox);
}
