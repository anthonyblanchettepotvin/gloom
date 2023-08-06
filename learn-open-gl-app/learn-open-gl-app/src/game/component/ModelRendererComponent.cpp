#include "ModelRendererComponent.h"

#include "../actor/Actor.h"

#include "TransformComponent.h"

ModelRendererComponent::ModelRendererComponent(Model* model)
	: m_Model(model)
{
}

void ModelRendererComponent::Render()
{
	if (parent && m_Model)
	{
		TransformComponent* transformComponent = parent->FindComponentByType<TransformComponent>();
		if (transformComponent)
		{
			m_Model->Render(transformComponent->GetModelTransformationMatrix(), transformComponent->GetNormalTransformationMatrix());
		}
	}
}
