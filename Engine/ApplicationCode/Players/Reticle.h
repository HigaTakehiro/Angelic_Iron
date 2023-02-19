#pragma once
#include "Sprite.h"
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

private: //�����o�ϐ�
	//���e�B�N��
	Sprite* reticle;
	//���e�B�N�����W
	DirectX::XMFLOAT2 reticlePos;
	//���e�B�N���T�C�Y
	DirectX::XMFLOAT2 reticleSize;

};
