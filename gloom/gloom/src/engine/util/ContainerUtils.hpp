#pragma once

#include <vector>

class ContainerUtils
{
public:
	template<typename T>
	static void EraseNullptrOccurrencesFromVector(std::vector<T*>& vector);

	template<typename T>
	static std::vector<T*> EraseNullptrOccurrencesFromVector(const std::vector<T*>& vector);

	template<typename T>
	static void EraseElementOccurrencesFromVector(std::vector<T*>& vector, T* element);

	template<typename T>
	static std::vector<T*> EraseElementOccurrencesFromVector(const std::vector<T*>& vector, T* element);
};

template<typename T>
inline void ContainerUtils::EraseNullptrOccurrencesFromVector(std::vector<T*>& vector)
{
	ContainerUtils::EraseElementOccurrencesFromVector<T>(vector, nullptr);
}

template<typename T>
inline std::vector<T*> ContainerUtils::EraseNullptrOccurrencesFromVector(const std::vector<T*>& vector)
{
	return ContainerUtils::EraseElementOccurrencesFromVector<T>(vector, nullptr);
}

template<typename T>
inline void ContainerUtils::EraseElementOccurrencesFromVector(std::vector<T*>& vector, T* element)
{
	vector.erase(std::remove(vector.begin(), vector.end(), element), vector.end());
}

template<typename T>
inline std::vector<T*> ContainerUtils::EraseElementOccurrencesFromVector(const std::vector<T*>& vector, T* element)
{
	std::vector<T*> copy(vector.begin(), vector.end());

	ContainerUtils::EraseElementOccurrencesFromVector(copy, element);

	return copy;
}
