#pragma once

#include <cstdint>

enum class AssetFlag : uint16_t
{
	None = 0,
	Missing = (1u << 1),
	Invalid = (1u << 2)
};

enum class AssetType : uint16_t
{
	None = 0,
	PNG,
	JPG, 
	Text,
	Video
};


	