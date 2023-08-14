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
#include "BulletManager.h"
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
	Object3d* GetBossObj() { return boss_; }
	/// <summary>
	/// �{�X�{��HP���擾
	/// </summary>
	/// <returns>�{�XHP</returns>
	float GetBossHp() { return hp_; }
	/// <summary>
	/// ���S�t���O�擾
	/// </summary>
	/// <returns>���S�t���O</returns>
	bool GetIsDead() { return isDead_; }
	/// <summary>
	/// ���[�r�[�t���O�擾
	/// </summary>
	/// <returns>���[�r�[�t���O</returns>
	bool GetIsMovie() { return isMovie_; }
	/// <summary>
	/// �{�X�V�[�����Z�b�g
	/// </summary>
	/// <param name="bossScene">�{�X�V�[��</param>
	void SetBossScene(BossScene* bossScene) { bossScene_ = bossScene; }
	/// <summary>
	/// �v���C���[���Z�b�g
	/// </summary>
	/// <param name="player">�v���C���[</param>
	void SetPlayer(BossScenePlayer* player) { player_ = player; }
	/// <summary>
	/// �e�Ǘ��N���X���Z�b�g
	/// </summary>
	/// <param name="bulletManager">�e�Ǘ��N���X</param>
	void SetBulletManager(BulletManager* bulletManager) { bulletManager_ = bulletManager; }
	/// <summary>
	/// �J�����ړ��^�C�~���O�t���O�擾
	/// </summary>
	/// <returns></returns>
	bool GetIsCameraMoveTiming() { return isCameraMoveTiming_; }
	/// <summary>
	/// ���[�r�[�G�t�F�N�g�^�C�~���O�擾
	/// </summary>
	/// <returns></returns>
	virtual bool GetIsMovieEffectTiming() = 0;

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
	Object3d* boss_;
	//�{�X�V�[��
	BossScene* bossScene_;
	//�v���C���[
	BossScenePlayer* player_;
	//�v���C���[���W
	Vector3 playerPos_;
	//���W
	Vector3 pos_;
	//��]�p
	Vector3 rot_;
	//�傫��
	Vector3 scale_;
	//�U����
	float attackPower_;
	//�̗�
	float hp_;
	//�s���N�[���^�C�}�[
	int32_t actionCoolTimer_;
	//�_���[�W�^�C�}�[
	int32_t damageTimer_;
	//��]����
	int32_t rotationTimer_;
	//�X���[���o�p�^�C�}�[
	int32_t delayTimer_;
	//�U���p�^�[��
	int32_t actionPattern_;
	//�_���[�W�t���O
	bool isDamage_ = false;
	//���S�t���O
	bool isDead_ = false;
	//���[�r�[�t���O
	bool isMovie_ = false;
	bool isCameraMoveTiming_ = false;
	//���S�^�C�}�[
	int32_t deadTimer_;
	//HP�o�[
	Sprite* hpBar_;
	Sprite* hpRedBar_;
	BulletManager* bulletManager_;

};