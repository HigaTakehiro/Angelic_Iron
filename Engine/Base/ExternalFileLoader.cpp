#include "ExternalFileLoader.h"
#include <fstream>

const std::string ExternalFileLoader::defaultDirectory = "Engine/Resources/GameData/";

std::stringstream ExternalFileLoader::ExternalFileOpen(const std::string& fileName)
{
	//ファイルストリーム
	std::ifstream file;
	std::stringstream fileData;
	fileData.str("");
	fileData.clear(std::stringstream::goodbit);

	file.open(defaultDirectory + fileName);
	if (file.fail()) {
		assert(0);
	}

	fileData << file.rdbuf();

	file.close();

	return fileData;
}
