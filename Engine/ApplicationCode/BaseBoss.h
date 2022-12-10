#pragma once
#include "Object3d.h"
#include "Model.h"
#include "ModelManager.h"
#include "Vector3.h"
#include "MouseInput.h"

class BaseBoss
{
public:
	virtual ~BaseBoss();

public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	virtual void Finalize();
	/// <summary>
	/// �s��
	/// </summary>
	virtual void Action();

protected: //�ÓI�����o�ϐ�
	//�U���N�[���^�C��
	static const int32_t actionCoolTime = 60;

protected: //�����o�ϐ�
	//�{�X�I�u�W�F�N�g
	Object3d* boss;
	//�v���C���[���W
	Vector3 playerPos;
	//���W
	Vector3 pos;
	//��]�p
	Vector3 rot;
	//�傫��
	Vector3 scale;
	//�U����
	float attackPower;
	//�̗�
	float hp;
};

