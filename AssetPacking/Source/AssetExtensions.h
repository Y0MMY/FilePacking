#pragma once

#include <string>
#include <unordered_map>

#include "AssetTypes.h"

inline static std::unordered_map<std::string, AssetType> s_AssetExtensionMap =
{
	{ ".png", AssetType::Image },
	{ ".jpg", AssetType::Image },
};


std::string GetExtensionFromType(AssetType type)
{
	switch (type)
	{
		case AssetType::None:
				return "None";
		case AssetType::Image:
			return "Image";
		case AssetType::Text:
			return "Text";
		case AssetType::Video:
			return "Video";
		case AssetType::Audio:
			return "Audio";

	}
	return "None";
}