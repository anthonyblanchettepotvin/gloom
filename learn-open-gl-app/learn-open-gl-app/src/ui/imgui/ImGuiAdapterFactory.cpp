#include "ImGuiAdapterFactory.h"

#include "../../engine/graphics/cubemap/Cubemap.h"
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

ImGuiAdapterFactory::ImGuiAdapterFactory(GraphicsEngine& graphicsEngine)
	: m_GraphicsEngine(graphicsEngine)
{
}

ImGuiAdapter* ImGuiAdapterFactory::CreateAdapter(Object* object) const
{
	if (Actor* actor = dynamic_cast<Actor*>(object))
		return new ImGuiActorAdapter(*this, *actor);
	if (Texture* texture = dynamic_cast<Texture*>(object))
		return new ImGuiTextureAdapter(m_GraphicsEngine, *texture);
	if (Cubemap* cubemap = dynamic_cast<Cubemap*>(object))
		return new ImGuiCubemapAdapter(*this, *cubemap);
	if (TransformComponent* castedComponent = dynamic_cast<TransformComponent*>(object))
		return new ImGuiTransformComponentAdapter(*castedComponent);
	if (PointLightComponent* castedComponent = dynamic_cast<PointLightComponent*>(object))
		return new ImGuiPointLightComponentAdapter(*castedComponent);
	if (DirectionalLightComponent* castedComponent = dynamic_cast<DirectionalLightComponent*>(object))
		return new ImGuiDirectionalLightComponentAdapter(*castedComponent);

	return nullptr;
}
