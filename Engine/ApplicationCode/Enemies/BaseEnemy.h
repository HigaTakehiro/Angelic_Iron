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
	/// <param name="modelName">���f����</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	virtual void Initialize(const ModelManager::ModelName modelName, const Vector3& pos, const Vector3& rot) = 0;
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
	/// ���b�N�I���t���O���Z�b�g
	/// </summary>
	/// <param name="isTarget"></param>
	void SetIsTarget(bool isTarget) { this->isTarget = isTarget; }
	/// <summary>
	/// ���S�t���O���擾
	/// </summary>
	/// <param name="isDead"></param>
	bool GetIsDead() { return isDead; }
	/// <summary>
	/// HP�擾
	/// </summary>
	/// <returns>HP</returns>
	int GetHP() { return hp; }
	/// <summary>
	/// ���[���V�[�����Z�b�g
	/// </summary>
	/// <param name="railScene"></param>
	void SetRailScene(RailScene* railScene) { this->railScene = railScene; }
	/// <summary>
	/// �v���C���[���Z�b�g
	/// </summary>
	/// <param name="player">�v���C���[</param>
	void SetPlayer(Player* player) { this->player = player; }
	/// <summary>
	/// ���b�N�I���t���O���Z�b�g
	/// </summary>
	/// <param name="isTarget">���b�N�I���t���O</param>
	void SetTarget(bool isTarget) { this->isTarget = isTarget; }
	/// <summary>
	/// ���b�N�I���t���O���擾
	/// </summary>
	/// <returns>���b�N�I���t���O</returns>
	bool GetIsTarget() { return isTarget; }
	/// <summary>
	/// �G�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�G�I�u�W�F�N�g</returns>
	Object3d* GetEnemyObj() { return enemy; }

protected: //�����o�֐�
	/// <summary>
	/// �ړ�����
	/// </summary>
	virtual void Move() = 0;
	/// <summary>
	/// �U������
	/// </summary>
	virtual void Attack() = 0;

	/// <summary>
	/// ���b�N�I�����o
	/// </summary>
	void RockOnPerformance();

protected: //�ÓI�����o�ϐ�
	//���b�N�I�����o�p����
	static const float targetReactionTime;
	//���S�����o�p����
	static const int32_t deadTime = 30;

protected: //�����o�ϐ�
	//�G�I�u�W�F�N�g
	Object3d* enemy;
	//���b�N�I���摜
	Sprite* target;
	//���W
	Vector3 pos;
	//�������W
	Vector3 oldPos;
	//�傫��
	Vector3 scale = { 5.0f, 5.0f, 5.0f };
	//��]�p
	Vector3 rot = {5.0f, 5.0f, 5.0f};
	//���S�t���O
	bool isDead;
	//���b�N�I���t���O
	bool isTarget;
	//�Q�[���V�[���̃|�C���^
	RailScene* railScene;
	//�v���C���[�̃|�C���^
	Player* player;
	//�̗�
	int hp;
	//�v���C���[�̍��W
	Vector3 playerPos;
	//��������
	int32_t lifeTimer;
	//�ő吶������
	int32_t lifeTime;
	//�e���ˊԊu����
	int32_t shotIntervalTimer;
	//�e���ˊԊu
	int32_t shotIntervalTime;
	//���S�����o�p����
	int32_t deadTimer;
	//���b�N�I�����o�p����
	float targetReactionTimer;
};