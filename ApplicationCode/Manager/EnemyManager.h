#pragma once
#include "BaseEnemy.h"
#include "Vector3.h"
#include <list>
#include <vector>

class EnemyManager
{
public: //�\����
	//�G�|�b�v�p���
	struct EnemyData {
		Vector3 pos_;
		Vector3 scale_;
		Vector3 rot_;
		std::vector<Vector3> movePoints_;
		std::string type_;
		int32_t moveTime_;
		int32_t lifeTime_;
		int32_t shotInterval_;
		int32_t hp_;
	};

public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyManager() = default;
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyManager() = default;
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
	/// �G�f�[�^�X�V����
	/// </summary>
	void LoadEnemyUpdate();

private: //�����o�ϐ�
	// �G�I�u�W�F�N�g���X�g
	std::list<std::unique_ptr<BaseEnemy>> enemies_;
	//�G�|�b�v�p��񃊃X�g
	std::list<EnemyData> enemyDatas_;
	//�|�b�v�ҋ@�t���O
	bool isWait_;
	//�C�e���[�^
	std::list<EnemyData>::iterator it_;
};

