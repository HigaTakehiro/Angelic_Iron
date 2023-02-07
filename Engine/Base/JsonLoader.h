#pragma once
#include <string>
#include <json.hpp>
#include <fstream>
#include <vector>
#include <list>
#include "Vector3.h"
#include "Object3d.h"
#include "ModelManager.h"

class JsonLoader
{
public:
	struct StageData {
		struct ObjectData {
			std::string  fileName;
			Vector3 transform;
			Vector3 rotation;
			Vector3 scaling;
		};
		std::vector<ObjectData> objects;
	};

public:
	JsonLoader() = default;
	~JsonLoader();

public: //�����o�֐�
	/// <summary>
	/// �X�e�[�W�f�[�^json�t�@�C���ǂݍ��݋y�ѐ���
	/// </summary>
	/// <param name="fileName">json�t�@�C��</param>
	void StageDataLoadandSet(const std::string fileName);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

private: //�ÓI�����o�ϐ�
	static const std::string baseDirectory;
	static const std::string extension;

private: //�����o�ϐ�
	std::list<std::unique_ptr<Object3d>> allObjects;
};

