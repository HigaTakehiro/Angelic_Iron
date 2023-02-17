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
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	/// <summary>
	/// �V�[���؂�ւ��t���O���擾����
	/// </summary>
	/// <returns>�V�[���؂�ւ��t���O</returns>
	bool GetIsSceneChange() { return isSceneChange; }

	/// <summary>
	/// �V�[���؂�ւ��J�n�t���O�𗧂Ă�
	/// </summary>
	/// <param name="isSceneChangeStart">�V�[���؂�ւ��J�n�t���O</param>
	void SetIsSceneChangeStart(bool isSceneChangeStart) { this->isSceneChangeStart = isSceneChangeStart; }

	/// <summary>
	/// �V�[���؂�ւ������t���O�𗧂Ă�
	/// </summary>
	/// <param name="isSceneChangeComplete">�V�[���؂�ւ������t���O</param>
	void SetIsSceneChangeComplete(bool isSceneChangeComplete) { this->isSceneChangeComplete = isSceneChangeComplete; }

private: //�����o�֐�

	/// <summary>
	/// �V�[���؂�ւ����o
	/// </summary>
	void SceneChangePerformance();

	/// <summary>
	/// �V�[���؂�ւ��������o
	/// </summary>
	void SceneChangeCompletePerformance();

private: //�ÓI�����o�ϐ�
	//�V�[���؂�ւ����o����
	const static int32_t sceneChangeTime;
	//�V�[���؂�ւ��^�C�}�[
	static int32_t sceneChangeTimer;
	//�V�[���؂�ւ��p�X�v���C�g
	static Sprite* sceneChangeEffects[10];
	//�V�[���؂�ւ��p�X�v���C�g���W
	static DirectX::XMFLOAT2 sceneChangeEffectsPos[10];
	//�V�[���؂�ւ��J�n�t���O
	static bool isSceneChangeStart;
	//�V�[���؂�ւ��t���O
	static bool isSceneChange;
	//�V�[���؂�ւ������t���O
	static bool isSceneChangeComplete;
};

