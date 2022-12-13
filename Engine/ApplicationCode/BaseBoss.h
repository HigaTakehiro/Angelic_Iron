#pragma once
#include "Object3d.h"
#include "Model.h"
#include "ModelManager.h"
#include "Vector3.h"
#include "MouseInput.h"
#include "SafeDelete.h"

class BaseBoss
{
public:
	virtual ~BaseBoss() {}

public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize(const ModelManager::ModelName model, const Vector3& pos) = 0;
	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update(const Vector3& playerPos, const int delayTime = 0) = 0;
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// �I������
	/// </summary>
	virtual void Finalize() = 0;
	/// <summary>
	/// �s��
	/// </summary>
	virtual void Action() = 0;

protected: //�ÓI�����o�ϐ�
	//�s���N�[���^�C��
	static const int32_t actionCoolTime;

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
	//�s���N�[���^�C�}�[
	int32_t actionCoolTimer;
	//�X���[���o�p�^�C�}�[
	int delayTimer;
};