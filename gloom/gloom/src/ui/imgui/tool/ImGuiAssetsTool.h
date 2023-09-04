#pragma once

#include <string>
#include <vector>

#define NEW_ASSET_NAME_MAXIMUM_SIZE 32

class ApplicationManager;
class Asset;
class AssetDescriptor;
class AssetManager;

class ImGuiAssetsTool
{
public:
    ImGuiAssetsTool(ApplicationManager& applicationManager, AssetManager& assetManager);
    ~ImGuiAssetsTool();

    void Render();

private:
    void RenderAssetsTabs();
    void RenderAllAssetsTab();
    void RenderAssetsTab(const AssetDescriptor& assetDescriptor);
    void RenderAssetsTab(const std::string& label, const std::vector<Asset*>& assets);
    void RenderAssetsTabRow(Asset& asset);

    void RenderCreateAssetButton();
    void RenderCreateAssetOption(const AssetDescriptor& assetDescriptor);
    void RenderCreateAssetModal();

    void SetupCreateAssetModal(const AssetDescriptor& assetDescriptor);
    void ClearCreateAssetModal();

    void CreateAndSelectAsset();

    bool ShouldRenderCreateAssetModal() const;

    ApplicationManager& m_ApplicationManager;
    AssetManager& m_AssetManager;

    char m_NewAssetNameBuffer[NEW_ASSET_NAME_MAXIMUM_SIZE] = "";
    const AssetDescriptor* m_NewAssetAssetDescriptor = nullptr;
};
