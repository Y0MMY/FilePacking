#pragma once

#include <cstdint>
#include <string>
#include <vector>

enum class AssetFlag : uint16_t
{
	None = 0,
	Missing = (1u << 1),
	Invalid = (1u << 2)
};

enum class AssetType : uint16_t
{
	None = 0,
	Image, 
	Text,
	Video,
	Audio
};

struct AssetInfo
{
	size_t m_Size;
	std::string m_Name;
	std::vector<char> m_Data;
	AssetType m_Type = AssetType::None;
};
	