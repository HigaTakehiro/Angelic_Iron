#pragma once
#include "Sprite.h"
#include "ImageManager.h"
#include <DirectXMath.h>

class SceneChangeEffect final
{
public: 
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneChangeEffect() = default;
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SceneChangeEffect() = default;
	/// <summary>
	/// �R�s�[�R���X�g���N�^���֎~
	/// </summary>
	SceneChangeEffect(const SceneChangeEffect& obj) = delete;
	/// <summary>
	/// ������Z�q���֎~
	/// </summary>
	SceneChangeEffect& operator=(const SceneChangeEffect& obj) = delete;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X���擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static SceneChangeEffect* GetIns();

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
	bool GetIsSceneChange() { return isSceneChange_; }

	/// <summary>
	/// �V�[���؂�ւ��J�n�t���O�𗧂Ă�
	/// </summary>
	/// <param name="isSceneChangeStart">�V�[���؂�ւ��J�n�t���O</param>
	void SetIsSceneChangeStart(bool isSceneChangeStart) { isSceneChangeStart_ = isSceneChangeStart; }

	/// <summary>
	/// �V�[���؂�ւ������t���O�𗧂Ă�
	/// </summary>
	/// <param name="isSceneChangeComplete">�V�[���؂�ւ������t���O</param>
	void SetIsSceneChangeComplete(bool isSceneChangeComplete) { isSceneChangeComplete_ = isSceneChangeComplete; }

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
	const static int32_t sceneChangeTime_;
	//�V�[���؂�ւ��^�C�}�[
	static int32_t sceneChangeTimer_;
	//�V�[���؂�ւ��p�X�v���C�g
	static Sprite* sceneChangeEffects_[10];
	//�V�[���؂�ւ��p�X�v���C�g���W
	static DirectX::XMFLOAT2 sceneChangeEffectsPos_[10];
	//�V�[���؂�ւ��J�n�t���O
	static bool isSceneChangeStart_;
	//�V�[���؂�ւ��t���O
	static bool isSceneChange_;
	//�V�[���؂�ւ������t���O
	static bool isSceneChangeComplete_;
};

