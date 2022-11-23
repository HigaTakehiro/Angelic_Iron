#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "ModelManager.h"
#include "EnemyBullet.h"
#include "GameScene.h"
#include "Sprite.h"
#include "Easing.h"

class GameScene;

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
	void Initialize(const std::string& modelName, const Vector3& pos, const Vector3& scale, const std::string& style);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(const XMFLOAT3& playerPos, float delayTime);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �摜�`�揈��
	/// </summary>
	void SpriteDraw();

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

	/// <summary>
	/// ���b�N�I���t���O���擾
	/// </summary>
	/// <returns></returns>
	bool GetIsTarget() { return isTarget; }

	/// <summary>
	/// �Q�[���V�[�����Z�b�g����
	/// </summary>
	/// <param name="gameScene">�Q�[���V�[��</param>
	void SetGamaScene(GameScene* gameScene) { this->gameScene = gameScene; }

	/// <summary>
	/// ���b�N�I���t���O�����Ă�
	/// </summary>
	/// <param name="isTarget"></param>
	void SetTarget(bool isTarget) { this->isTarget = isTarget; }

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

	/// <summary>
	/// �v���C���[���ˌ��͈͂ɂ��邩�ǂ���
	/// </summary>
	/// <param name="playerPos">�v���C���[�̍��W</param>
	/// <param name="enemyPos">�G�l�~�[�̍��W</param>
	/// <param name="range">�ˌ��͈�</param>
	/// <param name="playerScale">�v���C���[�̑傫��</param>
	/// <returns></returns>
	bool IsShotRangeJudge(const Vector3& playerPos, const Vector3& enemyPos, float range, float playerScale);

private: //�ÓI�����o�ϐ�
	static const int32_t shotIntervalTime = 60;
	static const int32_t lifeTime = 240;
	const float rotationTime = 60.0f;

private: //�����o�ϐ�

	int32_t shotIntervalTimer = shotIntervalTime;
	int32_t lifeTimer;
	Object3d* enemy;
	Sprite* target;
	GameScene* gameScene;
	Vector3 pos;
	Vector3 oldPos;
	float moveSpeedX;
	float moveSpeedY;
	EnemyStyle type;
	bool isDead;
	float delayCount;
	float rotationTimer;
	bool isTarget;
};

