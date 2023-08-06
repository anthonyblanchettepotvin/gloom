#include "ModelRendererComponent.h"

#include "../actor/Actor.h"

#include "TransformComponent.h"

ModelRendererComponent::ModelRendererComponent(Model* model)
	: model(model)
{
}

void ModelRendererComponent::Render()
{
	if (parent && model)
	{
		TransformComponent* transformComponent = parent->FindComponentByType<TransformComponent>();
		if (transformComponent)
		{
			model->Render(transformComponent->GetModelTransformationMatrix(), transformComponent->GetNormalTransformationMatrix());
		}
	}
}
