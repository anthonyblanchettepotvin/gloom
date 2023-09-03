#include "ImGuiAdapterFactory.h"

#include "../../engine/graphics/cubemap/Cubemap.h"
#include "../../engine/graphics/texture/Texture.h"
#include "../../engine/object/Object.h"
#include "../../game/actor/Actor.h"
#include "../../game/component/DirectionalLightComponent.h"
#include "../../game/component/PointLightComponent.h"
#include "../../game/component/TransformComponent.h"

#include "adapter/ImGuiActorAdapter.h"
#include "adapter/ImGuiCubemapAdapter.h"
#include "adapter/ImGuiDirectionalLightComponentAdapter.h"
#include "adapter/ImGuiPointLightComponentAdapter.h"
#include "adapter/ImGuiTextureAdapter.h"
#include "adapter/ImGuiTransformComponentAdapter.h"

ImGuiAdapterFactory::ImGuiAdapterFactory(GraphicsEngine& graphicsEngine)
	: m_GraphicsEngine(graphicsEngine)
{
}

std::unique_ptr<ImGuiAdapter> ImGuiAdapterFactory::CreateAdapter(Object* object)
{
	if (Actor* actor = dynamic_cast<Actor*>(object))
	{
		return std::make_unique<ImGuiActorAdapter>(*this, *actor);
	}

	if (Cubemap* cubemap = dynamic_cast<Cubemap*>(object))
	{
		return std::make_unique<ImGuiCubemapAdapter>(*this, *cubemap);
	}

	if (DirectionalLightComponent* castedComponent = dynamic_cast<DirectionalLightComponent*>(object))
	{
		return std::make_unique<ImGuiDirectionalLightComponentAdapter>(*castedComponent);
	}

	if (PointLightComponent* castedComponent = dynamic_cast<PointLightComponent*>(object))
	{
		return std::make_unique<ImGuiPointLightComponentAdapter>(*castedComponent);
	}

	if (Texture* texture = dynamic_cast<Texture*>(object))
	{
		return std::make_unique<ImGuiTextureAdapter>(m_GraphicsEngine, *texture);
	}

	if (TransformComponent* castedComponent = dynamic_cast<TransformComponent*>(object))
	{
		return std::make_unique<ImGuiTransformComponentAdapter>(*castedComponent);
	}

	return nullptr;
}
