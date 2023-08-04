#include "TestAssetRepository.h"

void TestAssetRepository::Add(TestAsset* testAsset)
{
	auto it = std::find(m_TestAssets.begin(), m_TestAssets.end(), testAsset);
	if (it == m_TestAssets.end())
	{
		m_TestAssets.push_back(testAsset);
	}
}

void TestAssetRepository::Remove(TestAsset* testAsset)
{
	auto it = std::find(m_TestAssets.begin(), m_TestAssets.end(), testAsset);
	if (it != m_TestAssets.end())
	{
		m_TestAssets.erase(it);
	}
}
