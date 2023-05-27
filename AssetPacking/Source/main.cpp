#include <iostream>
#include <fstream>

#include "AssetImporter.h"

int main()
{
	AssetImporter ai;
	//ai.AddResource("AssetImporter.cpp");
	//ai.AddResource("Assets/Images/1.png");
	//ai.AddResource("Assets/Images/2.jpg");
	auto v = AssetImporter::ReadFile("Image.bin");
	AssetImporter::WriteFileData(v[1]);
	//ai.Pack("");
	return 0;
}