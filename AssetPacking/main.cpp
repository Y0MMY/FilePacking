#include <iostream>
#include <fstream>

#include "AssetImporter.h"

int main()
{
	AssetImporter ai;
	//ai.AddResource("AssetImporter.cpp");
	//ai.AddResource("1.jpg");
	//ai.AddResource("zakon.jpg");
	auto v = AssetImporter::ReadFile("ImageJPG.bin");
	
	std::ofstream inputFile("ImageJPG2.jpg", std::ios::binary);
	inputFile.write((char*)v[1].m_Data.data(), v[1].m_Size);
	//ai.Pack("");
	return 0;
}