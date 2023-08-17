#pragma once

#include <string>
#include <vector>

#define NEW_ASSET_NAME_MAXIMUM_SIZE 32

class Asset;
class AssetDescriptor;
class AssetManager;

class ImGuiAssetsTool
{
public:
    ImGuiAssetsTool(AssetManager& assetManager);
    ~ImGuiAssetsTool();

    void RenderUi();

private:
    AssetManager& m_AssetManager;

    char m_NewAssetNameBuffer[NEW_ASSET_NAME_MAXIMUM_SIZE] = "";
    const AssetDescriptor* m_NewAssetAssetDescriptor = nullptr;

    void RenderAssetsTabs();
    void RenderAllAssetsTab();
    void RenderAssetsTab(const AssetDescriptor& assetDescriptor);
    void RenderAssetsTab(const std::string& label, const std::vector<Asset*>& assets);

    void RenderCreateAssetButton();
    void RenderCreateAssetOption(const AssetDescriptor& assetDescriptor);
    void RenderCreateAssetModal();
    bool ShouldRenderCreateAssetModal();
    void SetupCreateAssetModal(const AssetDescriptor& assetDescriptor);
    void ClearCreateAssetModal();
};
