#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
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
	void Initialize(const Vector3& pos, const Vector3& velocity, Object3d* playerObj = nullptr);

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
	bool IsDead() const { return isDead_; }

	/// <summary>
	/// �G�e�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�G�e�I�u�W�F�N�g</returns>
	Object3d* GetEnemyBulletObj() { return enemyBullet_; }

private: //�ÓI�����o�ϐ�
	static const int32_t lifeTime = 60 * 2;
	static const int32_t homingTime = 30;

private: //�����o�ϐ�
	Object3d* enemyBullet_;
	Object3d* playerObj_;
	Vector3 pos_;
	Vector3 velocity_;
	Vector3 initVelocity_;
	bool isDead_;
	bool isHoming_;
	int32_t lifeTimer_ = lifeTime;
	int32_t homingTimer_ = homingTime;
};

