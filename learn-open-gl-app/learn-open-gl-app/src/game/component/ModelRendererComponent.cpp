#include "ModelRendererComponent.h"

#include "../actor/Actor.h"

#include "TransformComponent.h"

ModelRendererComponent::ModelRendererComponent(GraphicsEngine& graphicsEngine, Model* model)
	: RendererComponent(graphicsEngine), m_Model(model)
{
}

void ModelRendererComponent::Render()
{
	if (parent && m_Model)
	{
		TransformComponent* transformComponent = parent->FindComponentByType<TransformComponent>();
		if (transformComponent)
		{
			m_Model->SetTransform(transformComponent->GetTransform());

			for (const auto& mesh : m_Model->GetMeshes())
			{
				m_GraphicsEngine.Render(*mesh);
			}
		}
	}
}
