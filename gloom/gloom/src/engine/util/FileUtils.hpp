#pragma once

#include <string>

class FileUtils
{
public:
	static std::string ExtractDirectoryFromFilePath(const std::string& filePath)
	{
		size_t lastSeparatorPosition = filePath.find_last_of("/\\");
		if (lastSeparatorPosition == std::string::npos)
		{
			return "";
		}

		return filePath.substr(0, lastSeparatorPosition);
	}

	static std::string ExtractFileNameFromFilePath(const std::string& filePath)
	{
		size_t lastSeparatorPosition = filePath.find_last_of("/\\");
		if (lastSeparatorPosition == std::string::npos)
		{
			return filePath;
		}

		return filePath.substr(lastSeparatorPosition + 1);
	}

	static std::string EraseFileExtensionFromFileName(const std::string& fileName)
	{
		size_t lastDotPosition = fileName.find_last_of('.');
		if (lastDotPosition == std::string::npos)
		{
			return fileName;
		}

		return fileName.substr(0, lastDotPosition);
	}
};
