#pragma once

#include <vector>

#include "AssetRepository.h"
#include "TestAsset.h"

class TestAssetRepository : public AssetRepository<TestAsset>
{
public:
	void Add(TestAsset* testAsset) override;
	void Remove(TestAsset* testAsset) override;

private:
	std::vector<TestAsset*> m_TestAssets;
};
