#pragma once

template<class T>
class AssetRepository
{
public:
	virtual void Add(T* asset) = 0;
	virtual void Remove(T* asset) = 0;
};
