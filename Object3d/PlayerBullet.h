#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"

class PlayerBullet
{
public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Vector3 pos);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �e�̏�Ԃ�n��
	/// </summary>
	/// <returns>�e�̏��</returns>
	bool IsDead() const { return isDead; }

private: //�����o�ϐ�
	Model* bulletModel;
	Object3d* bullet;
	Vector3 pos;
	Vector3 initPos;
	bool isDead;
};

