#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "ModelManager.h"
#include "safedelete.h"

class Bomb
{
public: 
	Bomb();
	~Bomb();

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="playerPos">�v���C���[�̈ʒu</param>
	/// <param name="enemyPos">���b�N�I�����ꂽ�G�̈ʒu</param>
	/// <param name="vetor">�x�N�g��</param>
	void Initialize(const Vector3& playerPos, Object3d* target, const DirectX::XMVECTOR& vector);

	/// <summary>
	/// �X�V
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
	/// ���S�t���O�擾
	/// </summary>
	/// <returns>���S�t���O</returns>
	bool GetIsDead() { return isDead_; }

	/// <summary>
	/// �e�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�e�I�u�W�F�N�g</returns>
	Object3d* GetBullet() { return bullet_; }

private: //�萔
	static const int32_t bombTime_ = 30;

private: //�����o�ϐ�
	Object3d* bullet_;
	Object3d* targetEnemy_;
	Vector3 bulletPos_;
	Vector3 enemyPos_;
	Vector3 initBulletPos_;
	float accel_;
	float maxAccel_;
	DirectX::XMVECTOR vector_;

	int32_t bombTimer_;

	bool isDead_;
	bool isUp_;
};

