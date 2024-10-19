#include "ModelRendererComponent.h"

#include "../../engine/graphics/model/Model.h"
#include "../../engine/graphics/scene/Scene.h"

#include "../actor/Actor.h"

#include "TransformComponent.h"

ModelRendererComponent::ModelRendererComponent(Model* model)
	: m_Model(model)
{
}

void ModelRendererComponent::RegisterToScene(Scene& scene)
{
	if (!m_Parent || !m_Model)
		return;

	TransformComponent* transformComponent = m_Parent->FindComponentByType<TransformComponent>();
	if (!transformComponent)
		return;
	
	m_Model->SetTransform(transformComponent->GetTransform());

	for (const auto& mesh : m_Model->GetMeshes())
	{
		scene.Register(*mesh);
	}
}

void ModelRendererComponent::UnregisterFromScene(Scene& scene)
{
	if (!m_Model)
		return;

	for (const auto& mesh : m_Model->GetMeshes())
	{
		scene.Unregister(*mesh);
	}
}
