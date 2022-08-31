#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "MatCalc.h"

class PlayerBullet
{
public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Vector3 pos, Vector3 velocity);

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

private: //�ÓI�����o�ϐ�
	static const int32_t lifeTime = 60 * 2;

private: //�����o�ϐ�
	Model* bulletModel;
	Object3d* bullet;
	Vector3 pos;
	bool isDead;
	int32_t lifeTimer = lifeTime;
	Vector3 velocity;
};

