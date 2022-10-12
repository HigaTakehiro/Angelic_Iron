#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "Player.h"
#include "ModelManager.h"

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
	/// �G�̏�Ԃ��擾
	/// </summary>
	/// <returns>�G�̏��</returns>
	bool IsDead() const { return isDead; }

	/// <summary>
	/// �G�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�G�I�u�W�F�N�g</returns>
	Object3d* GetEnemyObj() { return enemy; }

private: //�����o�֐�
	EnemyStyle stringToEnemyStyle(const std::string& type);

	/// <summary>
	/// �G�̍s��
	/// </summary>
	void EnemyAction();

private: //�����o�ϐ�

	Object3d* enemy;
	Vector3 pos;
	Vector3 oldPos;
	float moveSpeed;
	EnemyStyle type;
	bool isDead;
};

