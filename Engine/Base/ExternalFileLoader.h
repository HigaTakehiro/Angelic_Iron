#pragma once

#include <string>
#include <sstream>
#include "BaseEnemy.h"

class ExternalFileLoader
{
public:
	ExternalFileLoader() = default;
	~ExternalFileLoader() = default;

private: //�ÓI�����o�ϐ�
	//�f�t�H���g�t�@�C���p�X
	const static std::string defaultDirectory;

private: //�����o�֐�
	/// <summary>
	/// �O���t�@�C���ǂݍ���
	/// </summary>
	/// <param name="fileName">�t�@�C����</param>
	/// <returns>�t�@�C���f�[�^</returns>
	std::stringstream ExternalFileOpen(const std::string& fileName);

	/*/// <summary>
	/// �G�f�[�^�X�V����
	/// </summary>
	/// <param name="enemyData">�G�f�[�^</param>
	void EnemyDataUpdate(const std::stringstream& enemyData);

	/// <summary>
	/// ���b�Z�[�W�f�[�^�X�V����
	/// </summary>
	/// <param name="textMessageData">���b�Z�[�W�f�[�^</param>
	void TextMessageDataUpdate(const std::stringstream& textMessageData);*/
};

