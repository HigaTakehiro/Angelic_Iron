//#pragma once
//#include "BaseEnemy.h"
//#include "Vector3.h"
//#include "BulletManager.h"
//#include "RailScene.h"
//#include "ParticleManager.h"
//#include <list>
//#include <vector>
//#include <sstream>
//
//class EnemyManager
//{
//public: //�\����
//	//�G�|�b�v�p���
//	struct EnemyData {
//		Vector3 pos_;
//		Vector3 scale_;
//		Vector3 rot_;
//		std::vector<Vector3> movePoints_;
//		std::string type_;
//		float moveTime_;
//		int32_t lifeTime_;
//		int32_t shotInterval_;
//		int32_t hp_;
//		int32_t waitTime_;
//	};
//
//public: //�����o�֐�
//	/// <summary>
//	/// �R���X�g���N�^
//	/// </summary>
//	EnemyManager() = default;
//	/// <summary>
//	/// �f�X�g���N�^
//	/// </summary>
//	~EnemyManager() = default;
//	/// <summary>
//	/// ������
//	/// </summary>
//	void Initialize(const std::string& fileName);
//	/// <summary>
//	/// �X�V����
//	/// </summary>
//	void Update(bool isPause);
//	/// <summary>
//	/// �`�揈��
//	/// </summary>
//	void Draw();
//	/// <summary>
//	/// �X�v���C�g�`�揈��
//	/// </summary>
//	void SpriteDraw();
//	/// <summary>
//	/// �G�f�[�^�X�V����
//	/// </summary>
//	void EnemyDataUpdate(bool isPause);
//	/// <summary>
//	/// �G���o����
//	/// </summary>
//	void EnemyReactions(BaseEnemy* enmey);
//	/// <summary>
//	/// �G�f�[�^�ǂݍ��ݏ���
//	/// </summary>
//	void LoadEnemyData();
//	/// <summary>
//	/// ���b�N�I������
//	/// </summary>
//	void EnemyRockOnPerformance();
//	/// <summary>
//	/// �G���X�g�擾
//	/// </summary>
//	/// <returns></returns>
//	std::list<std::unique_ptr<BaseEnemy>>& GetEnemies() { return enemies_; }
//	/// <summary>
//	/// �e�Ǘ��}�l�[�W���[�Z�b�g
//	/// </summary>
//	/// <param name="bulletManager">�e�Ǘ��}�l�[�W��>
//	void SetBulletManager(BulletManager* bulletManager) { bulletManager_ = bulletManager; }
//	/// <summary>
//	/// ���[���V�[�����Z�b�g
//	/// </summary>
//	/// <param name="railScene">���[���V�[��</param>
//	void SetRailScene(RailScene* railScene) { railScene_ = railScene; }
//	/// <summary>
//	/// �v���C���[���Z�b�g
//	/// </summary>
//	/// <param name="player">�v���C���[</param>
//	void SetPlayer(Player* player) { player_ = player; }
//	/// <summary>
//	/// �p�[�e�B�N���}�l�[�W���[���Z�b�g
//	/// </summary>
//	/// <param name="particleManager">�p�[�e�B�N���}�l�[�W���[</param>
//	void SetParticleManager(ParticleManager* particleManager) { particles_ = particleManager; }
//	/// <summary>
//	/// �}�E�X�J�[�\���������Ă��邩�`�F�b�N
//	/// </summary>
//	/// <param name="enemy">�G</param>
//	/// <returns>�}�E�X�J�[�\�����������Ă���</returns>
//	bool IsTargetCheck(DirectX::XMFLOAT2 enemyPos);
//
//private: //�����o�ϐ�
//	// �G�I�u�W�F�N�g���X�g
//	std::list<std::unique_ptr<BaseEnemy>> enemies_;
//	//�G�|�b�v�p��񃊃X�g
//	std::list<EnemyData> enemyDatas_;
//	//�G�O���t�@�C���i�[�p������
//	std::stringstream enemyData_;
//	/// <summary>
//	/// �e�Ǘ��}�l�[�W���[
//	/// </summary>
//	BulletManager* bulletManager_;
//	/// <summary>
//	/// ���[���V�[��
//	/// </summary>
//	RailScene* railScene_;
//	/// <summary>
//	/// �v���C���[
//	/// </summary>
//	Player* player_;
//	//�|�b�v�ҋ@�t���O
//	bool isWait_;
//	//�ҋ@����
//	int32_t waitTimer_;
//	//�p�[�e�B�N��
//	ParticleManager* particles_;
//	//�C�e���[�^
//	std::list<EnemyData>::iterator it_;
//};
//
