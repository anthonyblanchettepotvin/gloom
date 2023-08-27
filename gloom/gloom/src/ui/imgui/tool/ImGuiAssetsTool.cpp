#include "ImGuiAssetsTool.h"

#include <cassert>

#include "../../../vendor/imgui/imgui.h"

#include "../../../application/ApplicationManager.h"
#include "../../../engine/asset/Asset.h"
#include "../../../engine/asset/AssetManager.h"
#include "../../../engine/asset/AssetDescriptor.h"

#include "../ImGuiUtils.hpp"

#define ASSETS_TOOL_NAME "Assets"

#define ASSETS_TAB_BAR_ID "_AssetsTab"
#define ASSETS_TAB_ALL_LABEL "All"

#define ASSETS_TABLE_ID "_AssetsTable"
#define ASSETS_TABLE_COLUMN_LABEL_ID "ID"
#define ASSETS_TABLE_COLUMN_LABEL_NAME "Name"
#define ASSETS_TABLE_COLUMN_LABEL_OBJECT_TYPE "Object Type"
#define ASSETS_TABLE_NB_COLUMNS 3

#define CREATE_ASSET_BUTTON_LABEL "Create Asset"
#define CREATE_ASSET_BUTTON_POPUP_OPTION_LABEL_PREFIX "Create "
#define CREATE_ASSET_POPUP_ID "_CreateAssetPopup"
#define CREATE_ASSET_POPUP_LABEL_PREFIX "Create "
#define CREATE_ASSET_POPUP_CONFIRM_BUTTON_LABEL "Confirm"
#define CREATE_ASSET_POPUP_CANCEL_BUTTON_LABEL "Cancel"
#define CREATE_ASSET_POPUP_ASSET_NAME_INPUT_LABEL_SUFFIX " Name"

ImGuiAssetsTool::ImGuiAssetsTool(ApplicationManager& applicationManager, AssetManager& assetManager)
	: m_ApplicationManager(applicationManager), m_AssetManager(assetManager)
{
}

ImGuiAssetsTool::~ImGuiAssetsTool()
{
    if (!m_NewAssetAssetDescriptor)
        return;

    delete m_NewAssetAssetDescriptor;
    m_NewAssetAssetDescriptor = nullptr;
}

void ImGuiAssetsTool::Render()
{
    ImGui::Begin(ASSETS_TOOL_NAME);

    RenderCreateAssetButton();
    RenderCreateAssetModal();

    RenderAssetsTabs();

    ImGui::End();
}

void ImGuiAssetsTool::RenderAssetsTabs()
{
    if (ImGui::BeginTabBar(ASSETS_TAB_BAR_ID))
    {
        RenderAllAssetsTab();

        for (auto const& assetDescriptor : m_AssetManager.GetAssetDescriptors())
        {
            RenderAssetsTab(assetDescriptor);
        }

        ImGui::EndTabBar();
    }
}

void ImGuiAssetsTool::RenderAllAssetsTab()
{
    auto assets = m_AssetManager.GetAssets();
    RenderAssetsTab(ASSETS_TAB_ALL_LABEL, assets);
}

void ImGuiAssetsTool::RenderAssetsTab(const AssetDescriptor& assetDescriptor)
{
    auto assets = m_AssetManager.FindAssetsByObjectType(assetDescriptor.GetObjectType());
    RenderAssetsTab(assetDescriptor.GetDisplayName(), assets);
}

void ImGuiAssetsTool::RenderAssetsTab(const std::string& label, const std::vector<Asset*>& assets)
{
    if (ImGui::BeginTabItem(label.c_str()))
    {
        static ImGuiTableFlags flags = ImGuiTableFlags_Resizable
            | ImGuiTableFlags_Reorderable
            | ImGuiTableFlags_Hideable
            | ImGuiTableFlags_RowBg
            | ImGuiTableFlags_BordersOuter
            | ImGuiTableFlags_BordersV
            | ImGuiTableFlags_NoBordersInBody
            | ImGuiTableFlags_ScrollY;

        if (ImGui::BeginTable(ASSETS_TABLE_ID, ASSETS_TABLE_NB_COLUMNS, flags))
        {
            ImGui::TableSetupColumn(ASSETS_TABLE_COLUMN_LABEL_ID);
            ImGui::TableSetupColumn(ASSETS_TABLE_COLUMN_LABEL_NAME);
            ImGui::TableSetupColumn(ASSETS_TABLE_COLUMN_LABEL_OBJECT_TYPE);

            ImGui::TableSetupScrollFreeze(0, 1); // Makes the headers row always visible.
            ImGui::TableHeadersRow();

            ImGuiListClipper clipper;
            clipper.Begin(assets.size());
            while (clipper.Step())
            {
                for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
                {
                    auto asset = assets[row];

                    assert(asset != nullptr);
                    
                    RenderAssetsTabRow(*asset);
                }
            }
            clipper.End();

            ImGui::EndTable();
        }

        ImGui::EndTabItem();
    }
}

void ImGuiAssetsTool::RenderAssetsTabRow(const Asset& asset)
{
    ImGui::PushID(asset.GetId().ToString().c_str());

    ImGui::TableGetRowIndex();
    ImGui::TableNextColumn();
    if (ImGui::Selectable(asset.GetId().ToString().c_str(), IsAssetSelected(asset), ImGuiSelectableFlags_SpanAllColumns))
    {
        assert(asset.GetObject() != nullptr);

        m_ApplicationManager.SelectObject(*asset.GetObject());
    }

    ImGui::TableNextColumn();
    ImGui::TextUnformatted(asset.GetName().c_str());

    ImGui::TableNextColumn();
    ImGui::TextUnformatted(asset.GetDescriptor().GetDisplayName().c_str());

    ImGui::PopID();
}

bool ImGuiAssetsTool::IsAssetSelected(const Asset& asset) const
{
    if (m_ApplicationManager.GetSelectedObject() == nullptr || asset.GetObject() == nullptr)
        return false;

    return m_ApplicationManager.GetSelectedObject() == asset.GetObject();
}

void ImGuiAssetsTool::RenderCreateAssetButton()
{
    ImGuiUtils::PushGreenButtonStyle();

    if (ImGui::Button(CREATE_ASSET_BUTTON_LABEL))
    {
        float createAssetPopupPositionX = ImGui::GetItemRectMax().x;
        float createAssetPopupPositionY = ImGui::GetItemRectMin().y;
        ImVec2 createAssetPopupPosition(createAssetPopupPositionX, createAssetPopupPositionY);
        ImGui::SetNextWindowPos(createAssetPopupPosition);

        ImGui::OpenPopup(CREATE_ASSET_POPUP_ID);
    }

    ImGuiUtils::PopGreenButtonStyle();

    if (ImGui::BeginPopupContextItem(CREATE_ASSET_POPUP_ID))
    {
        for (const auto& assetDescriptor : m_AssetManager.GetAssetDescriptors())
        {
            RenderCreateAssetOption(assetDescriptor);
        }

        ImGui::EndPopup();
    }
}

void ImGuiAssetsTool::RenderCreateAssetOption(const AssetDescriptor& assetDescriptor)
{
    std::string optionLabel = CREATE_ASSET_BUTTON_POPUP_OPTION_LABEL_PREFIX + assetDescriptor.GetDisplayName();
    if (ImGui::Selectable(optionLabel.c_str()))
    {
        SetupCreateAssetModal(assetDescriptor);
    }
}

void ImGuiAssetsTool::SetupCreateAssetModal(const AssetDescriptor& assetDescriptor)
{
    m_NewAssetAssetDescriptor = new AssetDescriptor(assetDescriptor);
}

void ImGuiAssetsTool::RenderCreateAssetModal()
{
    if (!ShouldRenderCreateAssetModal())
        return;

    assert(m_NewAssetAssetDescriptor != nullptr);

    std::string popupLabel = CREATE_ASSET_POPUP_LABEL_PREFIX + m_NewAssetAssetDescriptor->GetDisplayName();
    ImGui::OpenPopup(popupLabel.c_str());

    if (ImGui::BeginPopupModal(popupLabel.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        std::string assetNameInputLabel = m_NewAssetAssetDescriptor->GetDisplayName() + CREATE_ASSET_POPUP_ASSET_NAME_INPUT_LABEL_SUFFIX;
        ImGui::InputText(assetNameInputLabel.c_str(), m_NewAssetNameBuffer, IM_ARRAYSIZE(m_NewAssetNameBuffer));

        ImGuiUtils::PushGreenButtonStyle();

        if (ImGui::Button(CREATE_ASSET_POPUP_CONFIRM_BUTTON_LABEL))
        {
            CreateAndSelectAsset();

            ClearCreateAssetModal();
        }

        ImGuiUtils::PopGreenButtonStyle();

        ImGui::SameLine();

        if (ImGui::Button(CREATE_ASSET_POPUP_CANCEL_BUTTON_LABEL))
        {
            ClearCreateAssetModal();

            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

bool ImGuiAssetsTool::ShouldRenderCreateAssetModal()
{
    return m_NewAssetAssetDescriptor != nullptr;
}

void ImGuiAssetsTool::CreateAndSelectAsset()
{
    std::string newAssetName(m_NewAssetNameBuffer);
    Asset* newAsset = m_AssetManager.CreateBlankAsset(m_NewAssetAssetDescriptor->GetObjectType(), newAssetName);
    if (!newAsset)
        return;
    
    m_ApplicationManager.SelectObject(*newAsset->GetObject());
}

void ImGuiAssetsTool::ClearCreateAssetModal()
{
    memset(m_NewAssetNameBuffer, NULL, NEW_ASSET_NAME_MAXIMUM_SIZE);

    if (!m_NewAssetAssetDescriptor)
        return;

    delete m_NewAssetAssetDescriptor;
    m_NewAssetAssetDescriptor = nullptr;
}
