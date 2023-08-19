#include "ImGuiAdapterFactory.h"

#include "../../engine/graphics/texture/Texture.h"
#include "../../engine/object/Object.h"
#include "../../game/actor/Actor.h"
#include "../../game/component/TransformComponent.h"
#include "../../game/component/PointLightComponent.h"
#include "../../game/component/DirectionalLightComponent.h"

#include "ImGuiActorAdapter.h"
#include "ImGuiCubemapAdapter.h"
#include "ImGuiDirectionalLightComponentAdapter.h"
#include "ImGuiPointLightComponentAdapter.h"
#include "ImGuiTextureAdapter.h"
#include "ImGuiTransformComponentAdapter.h"

#include "../../infrastructure/graphics/engine/GlGraphicsEngine.h"

ImGuiAdapterFactory::ImGuiAdapterFactory(GraphicsEngine& graphicsEngine)
	: m_GraphicsEngine(graphicsEngine)
{
}

ImGuiAdapter* ImGuiAdapterFactory::CreateAdapter(Object* object) const
{
	if (Actor* actor = dynamic_cast<Actor*>(object))
		return new ImGuiActorAdapter(actor);
	if (Texture* texture = dynamic_cast<Texture*>(object))
		return new ImGuiTextureAdapter(*texture, m_GraphicsEngine); // TODO: Reorder to pass dependencies first
	if (Cubemap* cubemap = dynamic_cast<Cubemap*>(object))
		return new ImGuiCubemapAdapter(*this, *cubemap);

	return nullptr;
}

//UiComponentAdapter* ImGuiAdapterFactory::CreateComponentAdapter(ActorComponent* component) const
//{
//	if (TransformComponent* castedComponent = dynamic_cast<TransformComponent*>(component))
//		return new ImGuiTransformComponentAdapter(castedComponent);
//	if (PointLightComponent* castedComponent = dynamic_cast<PointLightComponent*>(component))
//		return new ImGuiPointLightComponentAdapter(castedComponent);
//	if (DirectionalLightComponent* castedComponent = dynamic_cast<DirectionalLightComponent*>(component))
//		return new ImGuiDirectionalLightComponentAdapter(castedComponent);
//
//	return nullptr;
//}
