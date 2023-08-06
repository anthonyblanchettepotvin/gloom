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

			m_GraphicsObjects.reserve(m_Model->GetMeshes().size());

			for (size_t i = 0; i < m_Model->GetMeshes().size(); i++)
			{
				GraphicsObject* graphicsObject = nullptr;
				if (i >= m_GraphicsObjects.size())
				{
					auto mesh = m_Model->GetMeshes().at(i);

					graphicsObject = m_GraphicsEngine.CreateGraphicsObject(*mesh);
					m_GraphicsObjects.push_back(graphicsObject);
				}
				else
				{
					graphicsObject = m_GraphicsObjects[i];
				}

				graphicsObject->Render();
			}
		}
	}
}
