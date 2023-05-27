#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include "AssetTypes.h"
#include "AssetInterface.h"

class AssetImporter : public Asset
{
public:
	bool Pack(const std::filesystem::path & outputPath, const std::string& extension = ".bin") override;
	void AddResource(const std::filesystem::path& inputPath) override;
	void PackAllResourñes(const std::filesystem::path& inputPath, const std::filesystem::path& outputPath) override {}
private:
	std::vector<char> ReadFileContents(const std::filesystem::path& filePath);
public:
	std::vector<AssetInfo> ReadFile(const std::filesystem::path& filePath) override;
	bool WriteFileData(const AssetInfo& asset, const std::filesystem::path& outputPath = "") override;
private:
	std::vector<AssetInfo> m_Assets;
};