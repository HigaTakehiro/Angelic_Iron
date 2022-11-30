#pragma once
#include <string>
#include <json.hpp>
#include <fstream>
#include <vector>
#include "Vector3.h"

class JsonLoader
{
public:
	struct LevelData {
		struct ObjectData {
			std::string  fileName;
			Vector3 transform;
			Vector3 rotation;
			Vector3 scaling;
		};
		std::vector<ObjectData> objects;
	};

public: //メンバ関数
	/// <summary>
	/// jsonファイル読み込み
	/// </summary>
	/// <param name="fileName">jsonファイル</param>
	void JsonFileLoad(const std::string fileName);


	LevelData& LoadLevelData();

private: //静的メンバ変数
	static const std::string baseDirectory;
	static const std::string extension;

private: //メンバ変数
};

