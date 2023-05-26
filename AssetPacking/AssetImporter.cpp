#include "AssetImporter.h"
#include "AssetExtensions.h"

#include <fstream>
#include <iostream>
#include <unordered_map>

std::vector<char> AssetImporter::ReadFileContents(const std::filesystem::path& filePath)
{
	std::vector<char> contents;

	std::ifstream inputFile(filePath, std::ios::binary);
	if (!inputFile)
	{
		return contents;
	}

	inputFile.seekg(0, std::ifstream::end);
	std::streampos fileSize = inputFile.tellg();
	inputFile.seekg(0, std::ifstream::beg);

	contents.resize(fileSize);

	if (!inputFile.read(contents.data(), fileSize))
	{
		contents.clear();
	}

	inputFile.close();

	return contents;
}

bool AssetImporter::Pack(const std::filesystem::path& outputPath)
{
	if (m_Assets.empty()) return false;

	std::unordered_map<AssetType, std::vector<Asset>> typeAssets;

	for (const auto& asset : m_Assets)
	{
		typeAssets[asset.m_Type].push_back(asset);
	}

	for (const auto& it : typeAssets)
	{
		AssetType type = it.first;
		std::filesystem::path filePath = outputPath / (GetExtensionFromType(type) + ".bin");
		std::ofstream outputFile(filePath, std::ios::binary | std::ios::trunc);

		if (!outputFile)
		{
			std::cout << "File can't be constructed: " << filePath << std::endl;
			return false;
		}

		//Write count of assets 
		size_t assetSize = it.second.size();
		outputFile.write(reinterpret_cast<const char*>(&assetSize), sizeof(size_t));

		for (const auto& asset : it.second)
		{
			// Write name length
			size_t nameLength = asset.m_Name.size();
			outputFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(size_t));

			// Write name
			outputFile.write(asset.m_Name.c_str(), nameLength);

			// Write data length
			size_t dataSize = asset.m_Data.size();
			outputFile.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));

			// Write data
			outputFile.write(asset.m_Data.data(), dataSize);

			// Write asset type
			outputFile.write(reinterpret_cast<const char*>(&asset.m_Type), sizeof(AssetType));
		}

		outputFile.close();
	}

	return true;
}

std::vector<AssetImporter::Asset> AssetImporter::ReadFile(const std::filesystem::path& filePath)
{
	std::ifstream inputFile(filePath, std::ios::binary);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open file: " << filePath << std::endl;
		return {};
	}

	std::vector<Asset> assets;

	// Read count of assets
	size_t assetSize;
	inputFile.read(reinterpret_cast<char*>(&assetSize), sizeof(size_t));

	for (size_t i = 0; i < assetSize; i++)
	{
		Asset asset;

		// Read name length
		size_t nameLength;
		inputFile.read(reinterpret_cast<char*>(&nameLength), sizeof(size_t));
		asset.m_Name.resize(nameLength);
		inputFile.read(asset.m_Name.data(), nameLength);

		// Read data length
		size_t dataSize;
		inputFile.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
		asset.m_Data.resize(dataSize);
		inputFile.read(asset.m_Data.data(), dataSize);

		// Read asset type
		inputFile.read(reinterpret_cast<char*>(&asset.m_Type), sizeof(AssetType));
		
		asset.m_Size = dataSize;
		assets.push_back(asset);
	}

	return assets;
}

void AssetImporter::AddResource(const std::filesystem::path& inputPath)
{
	if (!std::filesystem::exists(inputPath))
	{
		std::cout << "Файл не существует." << std::endl;
		return;
	}

	std::vector<char> fileContents = ReadFileContents(inputPath);
	if (fileContents.empty())
	{
		std::cout << "Не удалось прочитать содержимое файла." << std::endl;
		return;
	}

	m_Assets.push_back({ fileContents.size(), inputPath.filename().string(), fileContents, s_AssetExtensionMap[inputPath.extension().string()] });
}

