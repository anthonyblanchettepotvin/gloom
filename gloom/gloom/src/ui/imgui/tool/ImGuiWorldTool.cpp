#include "ImGuiWorldTool.h"

#include "../../../vendor/imgui/imgui.h"

#include "../../../application/ApplicationManager.h"
#include "../../../engine/asset/Asset.h"
#include "../../../engine/asset/AssetManager.h"
#include "../../../engine/object/Object.h"
#include "../../../engine/object/ObjectType.h"
#include "../../../game/GameManager.h"
#include "../../../game/actor/Actor.h"
#include "../../../game/world/World.h"

#define WORLD_TOOL_NAME "World"

#define LOADED_WORLD_COMBO_LABEL "Loaded World"
#define LOADED_WORLD_COMBO_DEFAULT_PREVIEW_VALUE "None"
#define LOADED_WORLD_COMBO_UNNAMED_PREVIEW_VALUE "Unnamed"

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
		if (worldAsset)
		{
			comboPreviewValue = worldAsset->GetName();
		}
		else
		{
			comboPreviewValue = LOADED_WORLD_COMBO_UNNAMED_PREVIEW_VALUE;
		}
	}

	if (ImGui::BeginCombo(LOADED_WORLD_COMBO_LABEL, comboPreviewValue.c_str()))
	{
		auto assets = m_AssetManager.FindAssetsByObjectType(ObjectType(typeid(World)));
		for (const auto& asset : assets)
		{
			if (!asset)
			{
				continue;
			}

			RenderLoadedWorldComboOption(*asset);
		}

		ImGui::EndCombo();
	}
}

void ImGuiWorldTool::RenderLoadedWorldComboOption(Asset& asset)
{
	World* world = dynamic_cast<World*>(asset.GetObject());

	if (ImGui::Selectable(asset.GetName().c_str(), m_GameManager.IsWorldLoaded(world)))
	{
		m_GameManager.LoadWorld(world);
	}
}

void ImGuiWorldTool::RenderActorsTree()
{
	World* loadedWorld = m_GameManager.GetLoadedWorld();
	if (!loadedWorld)
	{
		return;
	}

	auto actors = loadedWorld->GetActors();
	for (const auto& actor : actors)
	{
		if (!actor)
		{
			continue;
		}

		RenderActorTree(*actor);
	}
}

void ImGuiWorldTool::RenderActorTree(Actor& actor)
{
	ImGuiTreeNodeFlags treeNodeFlag = ImGuiTreeNodeFlags_OpenOnArrow
		| ImGuiTreeNodeFlags_OpenOnDoubleClick
		| ImGuiTreeNodeFlags_SpanAvailWidth
		| ImGuiTreeNodeFlags_Leaf;

	if (m_ApplicationManager.IsObjectSelected(&actor))
	{
		treeNodeFlag |= ImGuiTreeNodeFlags_Selected;
	}

	bool treeNodeOpened = ImGui::TreeNodeEx(actor.GetName().c_str(), treeNodeFlag);

	if (ImGui::IsItemClicked())
	{
		m_ApplicationManager.SelectObject(&actor);
	}

	if (treeNodeOpened)
	{
		ImGui::TreePop();
	}
}
