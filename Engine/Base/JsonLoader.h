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

public: //�����o�֐�
	/// <summary>
	/// json�t�@�C���ǂݍ���
	/// </summary>
	/// <param name="fileName">json�t�@�C��</param>
	void JsonFileLoad(const std::string fileName);


	LevelData& LoadLevelData();

private: //�ÓI�����o�ϐ�
	static const std::string baseDirectory;
	static const std::string extension;

private: //�����o�ϐ�
};

