#include "ImGuiAdapterFactory.h"

#include "../../Actor.h"

#include "../../components/TransformComponent.h"
#include "../../components/ModelRendererComponent.h"
#include "../../components/SpriteRendererComponent.h"
#include "../../components/PointLightComponent.h"
#include "../../components/DirectionalLightComponent.h"

#include "ImGuiActorAdapter.h"

#include "ImGuiTransformComponentAdapter.h"
#include "ImGuiModelRendererComponentAdapter.h"
#include "ImGuiSpriteRendererComponentAdapter.h"
#include "ImGuiPointLightComponentAdapter.h"
#include "ImGuiDirectionalLightComponentAdapter.h"

UiActorAdapter* ImGuiAdapterFactory::CreateActorAdapter(Actor* actor) const
{
	return new ImGuiActorAdapter(actor);
}

UiComponentAdapter* ImGuiAdapterFactory::CreateComponentAdapter(ActorComponent* component) const
{
	if (TransformComponent* castedComponent = dynamic_cast<TransformComponent*>(component))
		return new ImGuiTransformComponentAdapter(castedComponent);
	if (ModelRendererComponent* castedComponent = dynamic_cast<ModelRendererComponent*>(component))
		return new ImGuiModelRendererComponentAdapter(castedComponent);
	if (SpriteRendererComponent* castedComponent = dynamic_cast<SpriteRendererComponent*>(component))
		return new ImGuiSpriteRendererComponentAdapter(castedComponent);
	if (PointLightComponent* castedComponent = dynamic_cast<PointLightComponent*>(component))
		return new ImGuiPointLightComponentAdapter(castedComponent);
	if (DirectionalLightComponent* castedComponent = dynamic_cast<DirectionalLightComponent*>(component))
		return new ImGuiDirectionalLightComponentAdapter(castedComponent);
}
