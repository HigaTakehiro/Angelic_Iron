#pragma once
#include "Sprite.h"
#include "ImageManager.h"
#include <DirectXMath.h>

class SceneChange
{
public: 
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneChange() = default;
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SceneChange() = default;
	/// <summary>
	/// �R�s�[�R���X�g���N�^���֎~
	/// </summary>
	SceneChange(const SceneChange& obj) = delete;
	/// <summary>
	/// ������Z�q���֎~
	/// </summary>
	SceneChange& operator=(const SceneChange& obj) = delete;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X���擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static SceneChange* GetIns();

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �V�[���ύX�t���O���擾����
	/// </summary>
	/// <returns></returns>
	bool GetIsSceneChange() { return isSceneChange; }

	/// <summary>
	/// �V�[���ύX�����t���O�𗧂Ă�
	/// </summary>
	/// <param name="isSceneChangeComplete"></param>
	void SetIsSceneChangeComplete(bool isSceneChangeComplete) { this->isSceneChangeComplete = isSceneChangeComplete; }

public: //�ÓI�����o�ϐ�
	//�V�[���؂�ւ�����
	static int32_t sceneChangeTimer;
	//�V�[���؂�ւ��p�X�v���C�g
	static Sprite* sceneChangeEffects[10];
	//�V�[���؂�ւ��p�X�v���C�g���W
	static DirectX::XMFLOAT2 sceneChangeEffectPos[10];
	//�V�[���؂�ւ��J�n�t���O
	static bool isSceneChangeStart;
	//�V�[���؂�ւ��t���O
	static bool isSceneChange;
	//�V�[���؂�ւ������t���O
	static bool isSceneChangeComplete;
};

