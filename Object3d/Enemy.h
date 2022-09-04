#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "Player.h"

class Enemy
{
	enum EnemyStyle {
		STOP_PTAG,
		STOP_STR,
		UDMOVE_PTAG,
		UDMOVE_STR,
		LRMOVE_PTAG,
		LRMOVE_STR
	};

public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const std::string& modelName, Vector3 pos, Vector3 rot, Vector3 scale);

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

private: //�����o�ϐ�

	Model* enemyModel;
	Object3d* enemy;
	Vector3 pos;
	bool isDead;
};

