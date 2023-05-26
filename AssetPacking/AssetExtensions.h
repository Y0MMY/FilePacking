#pragma once

#include <string>
#include <unordered_map>

#include "AssetTypes.h"

inline static std::unordered_map<std::string, AssetType> s_AssetExtensionMap =
{
	{ ".png", AssetType::PNG },
	{ ".jpg", AssetType::JPG },
};


std::string GetExtensionFromType(AssetType type)
{
	switch (type)
	{
		case AssetType::None:
				return "None";
		case AssetType::JPG:
			return "ImageJPG";
		case AssetType::PNG:
			return "ImagePNG";
		case AssetType::Text:
			return "Text";
		case AssetType::Video:
			return "Video";

	}
	return "None";
}