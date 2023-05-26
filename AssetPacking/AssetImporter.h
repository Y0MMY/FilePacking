#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include "AssetTypes.h"

class AssetImporter
{
public:
	bool Pack(const std::filesystem::path & outputPath);
	void AddResource(const std::filesystem::path& inputPath);
	static void PackAllResourñes(const std::filesystem::path& inputPath, const std::filesystem::path& outputPath);
private:
	std::vector<char> ReadFileContents(const std::filesystem::path& filePath);
private:
	struct Asset
	{
		size_t m_Size;
		std::string m_Name;
		std::vector<char> m_Data;
		AssetType m_Type = AssetType::None;
	};
public:
	static std::vector<Asset> ReadFile(const std::filesystem::path& filePath);
private:
	std::vector<Asset> m_Assets;
};