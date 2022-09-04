#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "MatCalc.h"

class EnemyBullet
{
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
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	void OnCollision();

	/// <summary>
	/// �e�̏�Ԃ��擾
	/// </summary>
	/// <returns>�e�̏��</returns>
	bool IsDead() const { return isDead; }

	/// <summary>
	/// �G�e�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�G�e�I�u�W�F�N�g</returns>
	Object3d* GetEnemyBulletObj() { return enemyBullet; }

private: //�ÓI�����o�ϐ�
	static const int32_t lifeTime = 60 * 2;

private: //�����o�ϐ�
	Model* bulletModel;
	Object3d* enemyBullet;
	Vector3 Pos;
	bool isDead;
	int32_t lifeTimer = lifeTime;

};

