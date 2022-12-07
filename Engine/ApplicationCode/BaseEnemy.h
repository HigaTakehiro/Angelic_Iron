#pragma once

#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "ModelManager.h"
#include "EnemyBullet.h"
#include "RailScene.h"
#include "Sprite.h"
#include "Easing.h"

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
	/// <param name="scale">�傫��</param>
	virtual void Initialize(const ModelManager::ModelName modelName, const Vector3& pos, const Vector3& scale) = 0;
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="playerPos">�v���C���[�̍��W</param>
	/// <param name="delayTime">�X���[���o�p�x������</param>
	virtual void Update(const Vector3& playerPos, const int delayTime) = 0;
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// �摜�`�揈��
	/// </summary>
	virtual void SpriteDraw() = 0;
	/// <summary>
	/// �I������
	/// </summary>
	virtual void Finalize() = 0;
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
	/// ���[���V�[�����Z�b�g
	/// </summary>
	/// <param name="railScene"></param>
	void SetRailScene(RailScene* railScene) { this->railScene = railScene; }

protected: //�����o�֐�
	/// <summary>
	/// �ړ�����
	/// </summary>
	virtual void Move() = 0;
	/// <summary>
	/// �U������
	/// </summary>
	virtual void Attack() = 0;

protected: //�ÓI�����o�ϐ�
	//���b�N�I�����o�p����
	static const float targetReactionTime;

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
	Vector3 scale;
	//��]�p
	Vector3 rot;
	//���S�t���O
	bool isDead;
	//���b�N�I���t���O
	bool isTarget;
	//�Q�[���V�[���̃|�C���^
	RailScene* railScene;
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
	//���b�N�I�����o�p����
	float targetReactionTimer;
	//�X���[���o�p�^�C�}�[
	int delayTimer;
};