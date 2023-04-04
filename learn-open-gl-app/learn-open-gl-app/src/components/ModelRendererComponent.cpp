#include "ModelRendererComponent.h"

#include "../Actor.h"

#include "TransformComponent.h"

ModelRendererComponent::ModelRendererComponent(Model* model, Shader* shader)
	: RendererComponent(shader), model(model)
{
}

void ModelRendererComponent::Render()
{
	if (parent && shader && model)
	{
		TransformComponent* transformComponent = parent->FindComponentByType<TransformComponent>();
		if (transformComponent)
		{
			shader->setFloatMat4("modelXform", transformComponent->GetModelTransformationMatrix());
			shader->setFloatMat3("normalXform", transformComponent->GetNormalTransformationMatrix());

			model->Draw(shader);
		}
	}
}
