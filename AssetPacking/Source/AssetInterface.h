#pragma once

class Asset
{
public:
	virtual ~Asset() {}

	virtual bool Pack(const std::filesystem::path& outputPath, const std::string& extension = ".bin") = 0;
	virtual bool AddResource(const std::filesystem::path& inputPath) = 0;
	virtual void PackAllResources(const std::filesystem::path& inputPath, const std::filesystem::path& outputPath) = 0;
	virtual std::vector<AssetInfo> ReadFile(const std::filesystem::path& filePath) = 0;
	virtual bool WriteFileData(const AssetInfo& asset, const std::filesystem::path& outputPath) = 0;
};