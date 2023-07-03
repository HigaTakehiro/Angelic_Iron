#pragma once
#include "Object3d.h"
#include "ModelManager.h"
#include "Vector3.h"
#include "Camera.h"
#include "Sprite.h"
#include "ImageManager.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "MotionMath.h"
#include "SafeDelete.h"
#include "PlayerBullet.h"
#include "Easing.h"
#include "BossScene.h"
#include "BulletManager.h"
#include "Sound.h"

class BossScene;

class BossScenePlayer
{
public:
	BossScenePlayer() = default;
	~BossScenePlayer() = default;

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="camera">�J����</param>
	void Initialize(Camera* camera);
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �X�v���C�g�`��
	/// </summary>
	void SpriteDraw();
	/// <summary>
	/// �v���C���[�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns></returns>
	Object3d* GetPlayerObj() { return player_; }
	/// <summary>
	/// HP�擾
	/// </summary>
	/// <returns>HP</returns>
	int32_t GetHPCount() { return hpCount_; }
	/// <summary>
	/// �_���[�W�t���O�擾
	/// </summary>
	/// <returns>�_���[�W�t���O</returns>
	bool GetIsDamage() { return isDamage_; }
	/// <summary>
	/// ���S�t���O�擾
	/// </summary>
	/// <returns>���S�t���O</returns>
	bool GetIsDead() { return isDead_; }
	/// <summary>
	/// �_�b�V���t���O�擾
	/// </summary>
	/// <returns>�_�b�V���t���O</returns>
	bool GetIsDash() { return isDash_; }
	/// <summary>
	/// ���_�b�V���t���O�擾
	/// </summary>
	/// <returns>���_�b�V���t���O</returns>
	bool GetIsLeftDash() { return isLeftDash_; }
	/// <summary>
	/// �E�_�b�V���t���O�擾
	/// </summary>
	/// <returns>�E�_�b�V���t���O</returns>
	bool GetIsRightDash() { return isRightDash_; }
	/// <summary>
	/// �A���O���擾
	/// </summary>
	/// <returns>�A���O��</returns>
	float GetAngle() { return cameraAngle_; }
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();
	/// <summary>
	/// �q�b�g���R�[���o�b�N�֐�
	/// </summary>
	void OnCollision();
	/// <summary>
	/// �{�X�V�[�����Z�b�g
	/// </summary>
	/// <param name="bossScene">�{�X�V�[��</param>
	void SetBossScene(BossScene* bossScene) { bossScene_ = bossScene; }

	/// <summary>
	/// �e�Ǘ��N���X���Z�b�g
	/// </summary>
	/// <param name="bulletManeger">�e�Ǘ��N���X</param>
	void SetBulletManager(BulletManager* bulletManeger) { bulletManager_ = bulletManeger; }

private: //�����o�֐�
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// �_�b�V��
	/// </summary>
	void Dash();
	/// <summary>
	/// �W�����v
	/// </summary>
	void Jump();
	/// <summary>
	/// ���e�B�N���X�V
	/// </summary>
	void AimUpdate();
	/// <summary>
	/// �e����
	/// </summary>
	void Shot(Vector3 mouse3dPos);
	/// <summary>
	/// �_���[�W�G�t�F�N�g
	/// </summary>
	void DamageEffect();
	/// <summary>
	/// ���S���o
	/// </summary>
	void DeadPerformance();

private: //�ÓI�����o�ϐ�
	//��]����
	static const int32_t rotationTime;
	//�_�b�V������
	static const int32_t dashTime;
	//�e���ˊԊu
	static const int32_t shotCoolTime;
	//�ő�c�e��
	static const int32_t maxBulletCount = 16;
	//�ő�HP
	static const int32_t maxHp = 3;
	//�����[�h����
	static const int32_t reloadTime;
	//�ő�u�[�X�g��
	static const int32_t maxBoostCount = 3;
	//�u�[�X�g�񕜎���
	static const float boostReloadTime;
	//�_���[�W����
	static const int32_t damageTime;
	//���S�^�C��
	static const int32_t deadTime;

private: //�����o�ϐ�

	//3D�I�u�W�F�N�g
	//�v���C���[
	Object3d* player_;
	Object3d* gun_;

	//2D�X�v���C�g
	//���e�B�N��
	Sprite* playerUI_;
	Sprite* hpUI_[maxHp];
	Sprite* bulletUI_[maxBulletCount];
	Sprite* reloadUI_;
	Sprite* boostUI_[maxBoostCount];

	//�J����
	Camera* camera_;
	
	//�{�X�V�[��
	BossScene* bossScene_;
	//�T�E���h�N���X
	Sound* sound_;
	//�e�Ǘ��N���X
	BulletManager* bulletManager_;

	//�Q�[���V�[���p�ϐ�
	//��]����
	int32_t rotationTimer_;
	//�_�b�V���t���O
	bool isDash_;
	bool isLeftDash_;
	bool isRightDash_;
	//�_�b�V������
	int32_t dashTimer_;
	//�_�b�V���p�����A���O���ۑ�
	float initAngle_;
	//�W�����v�㏸���x
	float jumpPower_;
	//�W�����v�t���O
	bool isJump_;
	//�e���˃N�[���^�C�}�[
	int32_t shotCoolTimer_;
	//�e���˃t���O
	bool isShot_;
	//�e��
	int32_t bulletCount_;
	//HP
	int32_t hpCount_;
	//�����[�h�t���O
	bool isReload_;
	//�u�[�X�g�񕜃t���O
	bool isBoostReload_;
	//�u�[�X�g�񕜎���
	float boostReloadTimer_;
	//�u�[�X�g��
	int32_t boostCount_;
	//�����[�h����
	int32_t reloadTimer_;
	//���e�B�N�����W
	DirectX::XMFLOAT2 aimPos_;
	//���e�B�N��3D���W
	Vector3 aim3dPos_;
	//���[�J�����W
	Vector3 pos_;
	//��]�p
	Vector3 rot_;
	//�傫��
	Vector3 scale_;
	//�v���C���[���[���h���W
	Vector3 playerWPos_;
	//�J�����A���O��
	float cameraAngle_;
	//�J�������W
	Vector3 cameraPos_;
	//�_���[�W�t���O
	bool isDamage_;
	//�_���[�W�^�C�}�[
	int32_t damageTimer_;
	//���S�^�C�}�[
	int32_t deadTimer_;
	//���S�t���O
	bool isDead_;
};