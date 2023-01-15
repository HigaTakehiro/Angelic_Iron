#pragma once
#include "Sound.h"
#include <map>

class SoundManager final
{
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SoundManager() = default;
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SoundManager() = default;
	/// <summary>
	/// �R�s�[�R���X�g���N�^���֎~
	/// </summary>
	SoundManager(const SoundManager& obj) = delete;

	/// <summary>
	/// ������Z�q���֎~
	/// </summary>
	SoundManager& operator=(const SoundManager& obj) = delete;

public: //�T�u�N���X
	enum BGMKey {
		TITLE,
		STAGE1_RAIL,
		STAGE1_BOSS
	};

	enum SEKey {
		SHOT,
		PLAYER_DEAD,
		ENEMY_DEAD,
		RELOAD
	};

public:  //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static SoundManager* GetIns();

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="sound">�T�E���h�N���X�̃C���X�^���X</param>
	void Initialize(Sound* sound);
	
	/// <summary>
	/// BGM���Đ�
	/// </summary>
	/// <param name="bgmKey">�Đ�������BGM�}�b�v�̃L�[</param>
	/// <param name="isRoop">���[�v�Đ��t���O</param>
	/// <param name="volume">BGM����</param>
	void PlayBGM(const BGMKey bgmKey, const bool isRoop, const float volume);

	/// <summary>
	/// SE���Đ�
	/// </summary>
	/// <param name="seKey">�Đ�������SE�}�b�v�̃L�[</param>
	/// <param name="volume">SE����</param>
	void PlaySE(const SEKey seKey, const float volume);

	/// <summary>
	/// BGM���~
	/// </summary>
	/// <param name="bgmKey">��~������BGM�}�b�v�̃L�[</param>
	void StopBGM(const BGMKey bgmKey);

	/// <summary>
	/// SE���~
	/// </summary>
	/// <param name="seKey">��~������SE�}�b�v�̃L�[</param>
	void StopSE(const SEKey seKey);

private: //�����o�ϐ�

	/// <summary>
	/// BGM�ǉ�
	/// </summary>
	/// <param name="bgmKey">�ǉ�������BGM�}�b�v�̃L�[</param>
	/// <param name="fileName">�t�@�C����</param>
	void LoadBGM(const char* fileName, BGMKey bgmKey);

	/// <summary>
	/// SE�ǉ�
	/// </summary>
	/// <param name="seKey">�ǉ�������SE�}�b�v�̃L�[</param>
	/// <param name="fileName">�t�@�C����</param>
	void LoadSE(const char* fileName, SEKey seKey);

private: //�����o�ϐ�
	//�T�E���h�N���X�̃C���X�^���X
	Sound* sound = nullptr;
	//BGM�A�z�z��
	std::map<BGMKey, Sound::SoundData> bgmMap;
	//SE�A�z�z��
	std::map<SEKey, Sound::SoundData> seMap;
};
