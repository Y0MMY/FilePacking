#include <iostream>
#include <fstream>
#include <unordered_map>
#include <windows.h>

#include "AssetImporter.h"

enum class Action : uint32_t
{
	None = 0,
	Export,
	Import
};

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		std::unordered_map<std::string, std::string> helpMessages;
		helpMessages["--export"] = "Indicates that the assets should be packed";
		helpMessages["--import"] = "Indicates that the assets should be unpacked";
		helpMessages["-file"] = "What file of packed assets should be imported";
		helpMessages["-add"] = "Add the asset to the packing list";
		helpMessages["-path"] = "Specifies the path where to package or unpack the file";

		std::unordered_multimap<std::string, std::string> parameters;

		for (int i = 0; i < argc; i++)
		{
			std::string parameter = argv[i];
			if (parameter == "--help") {
				std::cout << std::endl << "=====================[AssetImporter]=====================" << std::endl << std::endl;
				std::cout << "Usage: [keys]=[values]" << std::endl;
				std::cout << "Avalibale keys:" << std::endl;

				for (const auto& pair : helpMessages) {
					std::cout << pair.first << ": " << pair.second << std::endl;
				}
				std::cout << "=====================[AssetImporter]=====================" << std::endl << std::endl;
				return 0;
			}

			if (parameter.substr(0,1) == "-")
			{
				auto delimeterPos = parameter.find("=", 1);
				if(delimeterPos != std::string::npos)
				{ 
					std::string key = parameter.substr(1, delimeterPos - 1);
					std::string value = parameter.substr(delimeterPos + 1);

					parameters.emplace(key,value);
				}
				else
				{
					std::string key = parameter.substr(1);

					parameters.emplace(key, "");
				}
			}
		}
		
		Action action = Action::None;
		std::string path;
		std::string readFile;
		AssetImporter ai;
		for (auto [key, value] : parameters)
		{
			if (key == "-export" && action == Action::None)
				action = Action::Export;

			else if (key == "-import" && action == Action::None)
			{
				action = Action::Import;
			}

			if (key == "add" && action == Action::Export)
				 ai.AddResource(value);
			
			if (key == "path" && path.empty())
			{
				path = value;
			}

			if (key == "file" && action == Action::Import)
			{
				readFile = value;
			}

			if (key == "path" && !readFile.empty())
			{
				auto data = ai.ReadFile(readFile);
				for (const auto file : data)
				{
					 ai.WriteFileData(file);
				}
			}
		}

		if (action == Action::Export)
		{
			
			if(ai.Pack(path))
				std::cout << "\033[1;32mFile assets was created\033[0m\n";
			else 
				std::cout << "\033[1;31mFile assets was not created\033[0m\n";
		}
	}

	return 0;
}