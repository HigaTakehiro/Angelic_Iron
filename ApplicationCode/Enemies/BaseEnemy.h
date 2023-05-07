#pragma once

#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "ModelManager.h"
#include "EnemyBullet.h"
#include "ImageManager.h"
#include "Sprite.h"
#include "Easing.h"

class RailScene;
class Player;

class BaseEnemy
{
public:
	virtual ~BaseEnemy() {};

public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="modelKey">���f���̃L�[</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	virtual void Initialize(const std::string modelKey, const Vector3& pos, const Vector3& rot) = 0;
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="playerPos">�v���C���[�̍��W</param>
	/// <param name="delayTime">�X���[���o�p�x������</param>
	virtual void Update() = 0;
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// �摜�`�揈��
	/// </summary>
	virtual void SpriteDraw() = 0;
	/// <summary>
	/// ���S�����o
	/// </summary>
	virtual void DeadPerformance() = 0;
	/// <summary>
	/// �U���q�b�g���R�[���o�b�N�֐�
	/// </summary>
	void OnCollision();
	/// <summary>
	/// �{���U���q�b�g���R�[���o�b�N�֐�
	/// </summary>
	void BombHitCollision();
	/// <summary>
	/// ���b�N�I���t���O���Z�b�g
	/// </summary>
	/// <param name="isTarget"></param>
	void SetIsTarget(bool isTarget) { isTarget_ = isTarget; }
	/// <summary>
	/// ���S�t���O���擾
	/// </summary>
	/// <param name="isDead"></param>
	bool GetIsDead() { return isDead_; }
	/// <summary>
	/// HP�擾
	/// </summary>
	/// <returns>HP</returns>
	int32_t GetHP() { return hp_; }
	/// <summary>
	/// ���[���V�[�����Z�b�g
	/// </summary>
	/// <param name="railScene"></param>
	void SetRailScene(RailScene* railScene) { railScene_ = railScene; }
	/// <summary>
	/// �v���C���[���Z�b�g
	/// </summary>
	/// <param name="player">�v���C���[</param>
	void SetPlayer(Player* player) { player_ = player; }
	/// <summary>
	/// ���b�N�I���t���O���Z�b�g
	/// </summary>
	/// <param name="isTarget">���b�N�I���t���O</param>
	void SetTarget(bool isTarget) { isTarget_ = isTarget; }
	/// <summary>
	/// �ړ����Ԃ��Z�b�g
	/// </summary>
	/// <param name="maxTime">�ړ�����</param>
	void SetMaxTime(float maxTime) { maxTime_ = maxTime; }
	/// <summary>
	/// �ő吶�����Ԃ��Z�b�g
	/// </summary>
	/// <param name="lifeTime">��������</param>
	void SetLifeTime(int32_t lifeTime) { lifeTime_ = lifeTime; }
	/// <summary>
	/// �e���ˊԊu���Z�b�g
	/// </summary>
	/// <param name="shotIntervalTime">�e���ˊԊu</param>
	void SetShotIntervalTime(int32_t shotIntervalTime) { shotIntervalTime_ = shotIntervalTime; }
	/// <summary>
	/// HP���Z�b�g
	/// </summary>
	/// <param name="hp">HP</param>
	void SetHP(int32_t hp) { hp_ = hp; }
	/// <summary>
	/// �ړ�����|�C���g���Z�b�g
	/// </summary>
	/// <param name="movePoints">�ړ��|�C���g</param>
	void SetMovePoints(const std::vector<Vector3>& movePoints) { movePoints_ = movePoints; }
	/// <summary>
	/// ���b�N�I���t���O���擾
	/// </summary>
	/// <returns>���b�N�I���t���O</returns>
	bool GetIsTarget() { return isTarget_; }
	/// <summary>
	/// �G�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�G�I�u�W�F�N�g</returns>
	Object3d* GetEnemyObj() { return enemy_; }
	/// <summary>
	/// ���b�N�I�����o
	/// </summary>
	void RockOnPerformance();

protected: //�����o�֐�
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// �_���[�W����
	/// </summary>
	void Damage();
	/// <summary>
	/// �U������
	/// </summary>
	virtual void Attack() = 0;

protected: //�ÓI�����o�ϐ�
	//���b�N�I�����o�p����
	static const float targetReactionTime;
	//���S�����o�p����
	static const int32_t deadTime = 30;
	//�_���[�W���o�p����
	static const int32_t damageTime = 12;

protected: //�����o�ϐ�
	//�G�I�u�W�F�N�g
	Object3d* enemy_;
	//���b�N�I���摜
	Sprite* target_;
	//���W
	Vector3 pos_;
	//�������W
	Vector3 oldPos_;
	//�傫��
	Vector3 scale_ = { 5.0f, 5.0f, 5.0f };
	//��]�p
	Vector3 rot_ = {5.0f, 5.0f, 5.0f};
	//���S�t���O
	bool isDead_;
	//���b�N�I���t���O
	bool isTarget_;
	//�_���[�W�t���O
	bool isDamage_;
	//�Q�[���V�[���̃|�C���^
	RailScene* railScene_;
	//�ړ�����|�C���g
	std::vector<Vector3> movePoints_;
	//���ݎ���
	float nowTimer_;
	//�o�ߎ���
	float elapsedTimer_;
	//�ړ�����
	float maxTime_ = 1.0f;
	//�]������
	float timeRate_;
	//�ړ����������|�C���g
	int32_t movedPoint_ = 0;
	//�v���C���[�̃|�C���^
	Player* player_;
	//�̗�
	int32_t hp_;
	//�v���C���[�̍��W
	Vector3 playerPos_;
	//��������
	int32_t lifeTimer_;
	//�ő吶������
	int32_t lifeTime_;
	//�e���ˊԊu����
	int32_t shotIntervalTimer_;
	//�e���ˊԊu
	int32_t shotIntervalTime_;
	//���S�����o�p����
	int32_t deadTimer_;
	//�_���[�W���o�p����
	int32_t damageTimer_;
	//���b�N�I�����o�p����
	float targetReactionTimer_;
};