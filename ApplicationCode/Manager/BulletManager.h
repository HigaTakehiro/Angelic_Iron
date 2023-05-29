#pragma once
#include "PlayerBullet.h"
#include "Bomb.h"
#include "EnemyBullet.h"
#include "BulletCase.h"

class BulletManager
{
public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BulletManager() = default;
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BulletManager() = default;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �v���C���[�e�ǉ�
	/// </summary>
	/// <param name="playerBullet">�v���C���[�e</param>
	void AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet);

	/// <summary>
	/// ��䰒ǉ�
	/// </summary>
	/// <param name="bulletCase">���</param>
	void AddBulletCase(std::unique_ptr<BulletCase> bulletCase);

	/// <summary>
	/// �G�e�ǉ�
	/// </summary>
	/// <param name="enemyBullet">�G�e</param>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet);

	/// <summary>
	/// �{���ǉ�
	/// </summary>
	/// <param name="bomb">�{��</param>
	void AddBomb(std::unique_ptr<Bomb> bomb);

	/// <summary>
	/// �v���C���[�e���X�g�擾
	/// </summary>
	/// <returns>�v���C���[�e���X�g</returns>
	const std::list<std::unique_ptr<PlayerBullet>>& GetPlayerBullets() { return playerBullets_; }

	/// <summary>
	/// �G�e���X�g�擾
	/// </summary>
	/// <returns>�G�e���X�g</returns>
	const std::list<std::unique_ptr<EnemyBullet>>& GetEnemyBullets() { return enemyBullets_; }

	/// <summary>
	/// �{�����X�g�擾
	/// </summary>
	/// <returns>�{�����X�g</returns>
	const std::list<std::unique_ptr<Bomb>>& GetBombs() { return bombs_; }

private: //�����o�ϐ�
	//�v���C���[�e���X�g
	std::list<std::unique_ptr<PlayerBullet>> playerBullets_;
	//�G�e���X�g
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	//�{�����X�g
	std::list<std::unique_ptr<Bomb>> bombs_;

	std::list<std::unique_ptr<BulletCase>> bulletCases_;
};