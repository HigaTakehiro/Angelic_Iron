#pragma once
#include "Object3d.h"
#include "Vector3.h"

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

protected: //�����o�ϐ�
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

