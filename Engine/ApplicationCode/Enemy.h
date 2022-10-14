#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "ModelManager.h"
#include "EnemyBullet.h"

class Player;

class Enemy
{
	enum class EnemyStyle {
		STOP_PTAG,
		STOP_STR,
		UDMOVE_PTAG,
		UDMOVE_STR,
		LRMOVE_PTAG,
		LRMOVE_STR
	};

public: //�R���X�g���N�^&�f�X�g���N�^
	Enemy();

	~Enemy();

public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const std::string& modelName, const Vector3& pos, const Vector3& rot, const Vector3& scale, const std::string& style);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(const XMFLOAT3& playerPos);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	void OnCollision();

	/// <summary>
	/// �e�̔��ˏ���
	/// </summary>
	void Shot();

	/// <summary>
	/// �G�̏�Ԃ��擾
	/// </summary>
	/// <returns>�G�̏��</returns>
	bool IsDead() const { return isDead; }

	/// <summary>
	/// �G�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�G�I�u�W�F�N�g</returns>
	Object3d* GetEnemyObj() { return enemy; }

	/// <summary>
	/// �G�^�C�v�擾
	/// </summary>
	/// <returns>�G�^�C�v</returns>
	EnemyStyle GetEnemyStyle() { return type; }

private: //�����o�֐�
	/// <summary>
	/// ��������G�l�~�[�^�C�v�ɕϊ�����
	/// </summary>
	/// <param name="type">�G�l�~�[�^�C�v(string)</param>
	/// <returns>�G�l�~�[�^�C�v(enum)</returns>
	EnemyStyle stringToEnemyStyle(const std::string& type);

	/// <summary>
	/// �G�̍s��
	/// </summary>
	void EnemyAction(const XMFLOAT3& playerPos);

private: //�ÓI�����o�ϐ�
	static const int32_t shotIntervalTime = 60;

private: //�����o�ϐ�

	int32_t shotIntervalTimer = shotIntervalTime;
	Object3d* enemy;
	Vector3 pos;
	Vector3 oldPos;
	float moveSpeedX;
	float moveSpeedY;
	EnemyStyle type;
	bool isDead;
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets;
};

