#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "MatCalc.h"
#include "safedelete.h"
#include "ModelManager.h"

class EnemyBullet
{
public: //�R���X�g���N�^&�f�X�g���N�^
	EnemyBullet();
	~EnemyBullet();

public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const Vector3& pos, const Vector3& velocity, bool isHoming = false);

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
	static const int32_t homingTime = 10;

private: //�����o�ϐ�
	Model* bulletModel;
	Object3d* enemyBullet;
	Vector3 pos;
	Vector3 velocity;
	bool isDead;
	bool isHoming;
	int32_t lifeTimer = lifeTime;
	int32_t homingTimer = homingTime;
};

