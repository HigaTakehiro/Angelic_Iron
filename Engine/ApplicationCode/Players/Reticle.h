#pragma once
#include "Sprite.h"
#include "ImageManager.h"
#include "DirectXMath.h"

class Reticle final
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Reticle() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Reticle() = default;

	/// <summary>
	/// �R�s�[�R���X�g���N�^���֎~
	/// </summary>
	Reticle(const Reticle& obj) = delete;

	/// <summary>
	/// ������Z�q���֎~
	/// </summary>
	Reticle& operator=(const Reticle& obj) = delete;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static Reticle* GetIns();

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
	/// ���e�B�N�����W���擾
	/// </summary>
	/// <returns>���e�B�N�����W</returns>
	DirectX::XMFLOAT2 GetPos() { return reticlePos; }

	/// <summary>
	/// ���e�B�N�����{�^���܂��͓G�ɂ����Ă���t���O���擾
	/// </summary>
	/// <returns></returns>
	bool GetIsSelectReticle() { return isSeletctReticle; }

	/// <summary>
	/// ���e�B�N�����{�^���܂��͓G�ɂ����Ă���t���O�𗧂Ă�
	/// </summary>
	/// <param name="isSelectReticle">���e�B�N�����{�^���܂��͓G�ɂ����Ă���t���O</param>
	void SetIsSelectReticle(bool isSelectReticle) { this->isSeletctReticle = isSelectReticle; }

private: //�ÓI�����o�ϐ�
	//���e�B�N����]����
	const static int32_t rotTime;

	//���e�B�N��
	static Sprite* reticle;
	//���e�B�N�����W
	static DirectX::XMFLOAT2 reticlePos;
	//���e�B�N���T�C�Y
	static DirectX::XMFLOAT2 reticleSize;
	//���e�B�N���p�x
	static float reticleRot;
	//���e�B�N�����{�^���܂��͓G�ɂ����Ă���t���O
	static bool isSeletctReticle;

private: //�����o�ϐ�
	//���e�B�N����]�^�C�}�[
	int32_t rotTimer;
};
