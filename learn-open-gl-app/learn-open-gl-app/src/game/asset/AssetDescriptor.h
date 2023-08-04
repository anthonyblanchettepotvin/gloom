#pragma once

#include "AssetDescriptorBase.h"
#include "AssetLoader.h"
#include "AssetRepository.h"

template<class T>
class AssetDescriptor : public AssetDescriptorBase
{
public:
	AssetDescriptor(AssetLoader<T>& assetLoader, AssetRepository<T>& assetRepository);

	AssetLoader<T>& GetAssetLoader() const { return m_AssetLoader; }
	AssetRepository<T>& GetAssetRepository() const { return m_AssetRepository; }

private:
	AssetLoader<T>& m_AssetLoader;
	AssetRepository<T>& m_AssetRepository;
};

template<class T>
inline AssetDescriptor<T>::AssetDescriptor(AssetLoader<T>& assetLoader, AssetRepository<T>& assetRepository)
	: AssetDescriptorBase(typeid(T)), m_AssetLoader(assetLoader), m_AssetRepository(assetRepository)
{
};
