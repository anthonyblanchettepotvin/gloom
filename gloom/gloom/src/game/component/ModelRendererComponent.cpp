#include "ModelRendererComponent.h"

#include "../../engine/graphics/engine/GraphicsEngine.h"
#include "../../engine/graphics/model/Model.h"

#include "../actor/Actor.h"

#include "TransformComponent.h"

ModelRendererComponent::ModelRendererComponent(GraphicsEngine& graphicsEngine, Model* model)
	: RendererComponent(graphicsEngine), m_Model(model)
{
}

void ModelRendererComponent::Render()
{
	if (!m_Parent || !m_Model)
	{
		return;
	}

	TransformComponent* transformComponent = m_Parent->FindComponentByType<TransformComponent>();
	if (!transformComponent)
	{
		return;
	}
	
	m_Model->SetTransform(transformComponent->GetTransform());

	for (const auto& mesh : m_Model->GetMeshes())
	{
		m_GraphicsEngine.Render(*mesh);
	}
}
