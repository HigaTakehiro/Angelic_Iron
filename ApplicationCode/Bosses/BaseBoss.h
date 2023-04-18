#pragma once
#include "Object3d.h"
#include "Model.h"
#include "ModelManager.h"
#include "Vector3.h"
#include "MouseInput.h"
#include "SafeDelete.h"
#include "EnemyBullet.h"
#include "MotionMath.h"
#include "ImageManager.h"
#include "Sprite.h"

class BossScene;
class BossScenePlayer;

class BaseBoss
{
public:
	virtual ~BaseBoss() {}

public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize(const std::string modelKey, const Vector3& pos) = 0;
	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update(const Vector3& playerPos, const int32_t delayTime = 0) = 0;
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
	/// �s��
	/// </summary>
	virtual void Action() = 0;
	/// <summary>
	/// ���[�r�[���o�s��
	/// </summary>
	virtual void MovieAction() = 0;
	/// <summary>
	/// �U���q�b�g���R�[���o�b�N�֐�
	/// </summary>
	void OnCollision();
	/// <summary>
	/// �_���[�W���A�N�V����
	/// </summary>
	void DamageReaction();
	/// <summary>
	/// �{�X�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns></returns>
	Object3d* GetBossObj() { return boss; }
	/// <summary>
	/// �{�X�{��HP���擾
	/// </summary>
	/// <returns>�{�XHP</returns>
	float GetBossHp() { return hp; }
	/// <summary>
	/// ���S�t���O�擾
	/// </summary>
	/// <returns>���S�t���O</returns>
	bool GetIsDead() { return isDead; }
	/// <summary>
	/// ���[�r�[�t���O�擾
	/// </summary>
	/// <returns>���[�r�[�t���O</returns>
	bool GetIsMovie() { return isMovie; }
	/// <summary>
	/// �{�X�V�[�����Z�b�g
	/// </summary>
	/// <param name="bossScene">�{�X�V�[��</param>
	void SetBossScene(BossScene* bossScene) { this->bossScene = bossScene; }
	/// <summary>
	/// �v���C���[���Z�b�g
	/// </summary>
	/// <param name="player">�v���C���[</param>
	void SetPlayer(BossScenePlayer* player) { this->player = player; }

protected: //�ÓI�����o�ϐ�
	//�s���N�[���^�C��
	static const int32_t actionCoolTime;
	//�_���[�W�^�C��
	static const int32_t damageTime;
	//��]����
	static const int32_t rotationTime;
	//���S����
	static const int32_t deadTime;
	//�_���[�W�J���[
	static const DirectX::XMFLOAT4 damageColor;
	//���SHP
	static const int32_t deadHP;

protected: //�����o�ϐ�
	//�{�X�I�u�W�F�N�g
	Object3d* boss;
	//�{�X�V�[��
	BossScene* bossScene;
	//�v���C���[
	BossScenePlayer* player;
	//�v���C���[���W
	Vector3 playerPos;
	//���W
	Vector3 pos;
	//��]�p
	Vector3 rot;
	//�傫��
	Vector3 scale;
	//�U����
	float attackPower;
	//�̗�
	float hp;
	//�s���N�[���^�C�}�[
	int32_t actionCoolTimer;
	//�_���[�W�^�C�}�[
	int32_t damageTimer;
	//��]����
	int32_t rotationTimer;
	//�X���[���o�p�^�C�}�[
	int32_t delayTimer;
	//�U���p�^�[��
	int32_t actionPattern;
	//�_���[�W�t���O
	bool isDamage = false;
	//���S�t���O
	bool isDead = false;
	//���[�r�[�t���O
	bool isMovie = false;
	//���S�^�C�}�[
	int32_t deadTimer;
	//HP�o�[
	Sprite* hpBar;
	Sprite* hpRedBar;
};