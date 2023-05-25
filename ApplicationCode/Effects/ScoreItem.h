#pragma once
#include "Player.h"
#include "Object3d.h"
#include "Vector3.h"
#include "ParticleManager.h"
#include "Camera.h"

class Player;

class ScoreItem
{
public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ScoreItem() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ScoreItem();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name="player">�v���C���[</param>
	/// <param name="camera">�J����</param>
	void Initialize(const Vector3& pos, Player* player, Camera* camera);

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
	/// ���S�t���O�擾
	/// </summary>
	/// <returns>���S�t���O</returns>
	bool GetIsDead() { return isDead_; }

	/// <summary>
	/// �X�R�A�A�C�e���擾
	/// </summary>
	/// <returns>�X�R�A�A�C�e��</returns>
	Object3d* GetScoreItemObj() { return scoreItem_; }

private: //�ÓI�����o�ϐ�
	//�ҋ@����
	static const int32_t standByTime = 60;

	//�ړ�����
	static const float moveTime;

private: //�����o�ϐ�
	//�X�R�A�A�C�e���I�u�W�F�N�g
	Object3d* scoreItem_;
	//�p�[�e�B�N��
	ParticleManager* particle_;
	//�v���C���[
	Player* player_;
	//���S�t���O
	bool isDead_;
	//���W
	Vector3 pos_;
	//��]�p�x
	Vector3 rot_;
	//�傫��
	Vector3 scale_;
	//�ҋ@�^�C�}�[
	int32_t standByTimer_;
	//�ړ��^�C�}�[
	float moveTimer_;
};

