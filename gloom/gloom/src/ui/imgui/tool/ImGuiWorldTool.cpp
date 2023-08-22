#include "ImGuiWorldTool.h"

#include <cassert>

#include "../../../vendor/imgui/imgui.h"

#include "../../../application/ApplicationManager.h"
#include "../../../engine/asset/Asset.h"
#include "../../../engine/asset/AssetManager.h"
#include "../../../engine/object/Object.h"
#include "../../../engine/object/ObjectType.h"
#include "../../../game/actor/Actor.h"
#include "../../../game/GameManager.h"
#include "../../../game/world/World.h"

#define WORLD_TOOL_NAME "World"

#define LOADED_WORLD_COMBO_LABEL "Loaded World"
#define LOADED_WORLD_COMBO_DEFAULT_PREVIEW_VALUE "None"

ImGuiWorldTool::ImGuiWorldTool(ApplicationManager& applicationManager, AssetManager& assetManager, GameManager& gameManager)
	: m_ApplicationManager(applicationManager), m_AssetManager(assetManager), m_GameManager(gameManager)
{
}

void ImGuiWorldTool::Render()
{
	ImGui::Begin(WORLD_TOOL_NAME);

	RenderLoadedWorldCombo();

	ImGui::Separator();

	RenderActorsTree();

	ImGui::End();
}

void ImGuiWorldTool::RenderLoadedWorldCombo()
{
	std::string comboPreviewValue = LOADED_WORLD_COMBO_DEFAULT_PREVIEW_VALUE;

	World* loadedWorld = m_GameManager.GetLoadedWorld();
	if (loadedWorld)
	{
		Asset* worldAsset = m_AssetManager.FindAssetByObjectId(loadedWorld->GetId());

		assert(worldAsset != nullptr);

		comboPreviewValue = worldAsset->GetName();
	}

	if (ImGui::BeginCombo(LOADED_WORLD_COMBO_LABEL, comboPreviewValue.c_str()))
	{
		auto assets = m_AssetManager.FindAssetsByObjectType(ObjectType(typeid(World)));
		for (const auto& asset : assets)
		{
			assert(asset != nullptr);

			World* world = dynamic_cast<World*>(asset->GetObject());

			assert(world != nullptr);

			RenderLoadedWorldComboOption(*world);
		}

		ImGui::EndCombo();
	}
}

void ImGuiWorldTool::RenderLoadedWorldComboOption(World& world)
{
	Asset* worldAsset = m_AssetManager.FindAssetByObjectId(world.GetId());

	assert(worldAsset != nullptr);

	if (ImGui::Selectable(worldAsset->GetName().c_str(), IsWorldLoaded(world)))
	{
		m_GameManager.LoadWorld(world);
	}
}

bool ImGuiWorldTool::IsWorldLoaded(const World& world) const
{
	if (m_GameManager.GetLoadedWorld() == nullptr)
		return false;

	return m_GameManager.GetLoadedWorld() == &world;
}

void ImGuiWorldTool::RenderActorsTree()
{
	World* loadedWorld = m_GameManager.GetLoadedWorld();
	if (!loadedWorld)
		return;

	auto actors = loadedWorld->GetActors();
	for (const auto& actor : actors)
	{
		assert(actor != nullptr);

		RenderActorTree(*actor);
	}
}

void ImGuiWorldTool::RenderActorTree(Actor& actor)
{
	ImGuiTreeNodeFlags treeNodeFlag = ImGuiTreeNodeFlags_OpenOnArrow
		| ImGuiTreeNodeFlags_OpenOnDoubleClick
		| ImGuiTreeNodeFlags_SpanAvailWidth
		| ImGuiTreeNodeFlags_Leaf;

	if (IsObjectSelected(actor))
	{
		treeNodeFlag |= ImGuiTreeNodeFlags_Selected;
	}

	bool treeNodeOpened = ImGui::TreeNodeEx(actor.GetName().c_str(), treeNodeFlag);

	if (ImGui::IsItemClicked())
	{
		m_ApplicationManager.SelectObject(actor);
	}

	if (treeNodeOpened)
	{
		ImGui::TreePop();
	}
}

bool ImGuiWorldTool::IsObjectSelected(const Object& object) const
{
	if (m_ApplicationManager.GetSelectedObject() == nullptr)
		return false;

	return m_ApplicationManager.GetSelectedObject() == &object;
}
