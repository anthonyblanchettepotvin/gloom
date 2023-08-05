#pragma once

#include <vector>

template<class T>
class AssetRepository
{
public:
	virtual void Add(T* asset);
	virtual void Remove(T* asset);

protected:
	std::vector<T*> m_Assets;
};

template<class T>
void AssetRepository<T>::Add(T* asset)
{
	auto it = std::find(m_Assets.begin(), m_Assets.end(), asset);
	if (it == m_Assets.end())
	{
		m_Assets.push_back(asset);
	}
}

template<class T>
void AssetRepository<T>::Remove(T* asset)
{
	auto it = std::find(m_Assets.begin(), m_Assets.end(), asset);
	if (it != m_Assets.end())
	{
		m_Assets.erase(it);
	}
}
