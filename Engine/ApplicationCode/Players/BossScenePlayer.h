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
	Object3d* GetPlayerObj() { return player; }
	/// <summary>
	/// HP�擾
	/// </summary>
	/// <returns>HP</returns>
	int32_t GetHPCount() { return hpCount; }
	/// <summary>
	/// �_���[�W�t���O�擾
	/// </summary>
	/// <returns>�_���[�W�t���O</returns>
	bool GetIsDamage() { return isDamage; }
	/// <summary>
	/// ���S�t���O�擾
	/// </summary>
	/// <returns>���S�t���O</returns>
	bool GetIsDead() { return isDead; }
	/// <summary>
	/// �_�b�V���t���O�擾
	/// </summary>
	/// <returns>�_�b�V���t���O</returns>
	bool GetIsDash() { return isDash; }
	/// <summary>
	/// ���_�b�V���t���O�擾
	/// </summary>
	/// <returns>���_�b�V���t���O</returns>
	bool GetIsLeftDash() { return isLeftDash; }
	/// <summary>
	/// �E�_�b�V���t���O�擾
	/// </summary>
	/// <returns>�E�_�b�V���t���O</returns>
	bool GetIsRightDash() { return isRightDash; }
	/// <summary>
	/// �A���O���擾
	/// </summary>
	/// <returns>�A���O��</returns>
	float GetAngle() { return cameraAngle; }
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
	void SetBossScene(BossScene* bossScene) { this->bossScene = bossScene; }

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
	Object3d* player;
	Object3d* gun;

	//2D�X�v���C�g
	//���e�B�N��
	Sprite* playerUI;
	Sprite* hpUI[maxHp];
	Sprite* bulletUI[maxBulletCount];
	Sprite* reloadUI;
	Sprite* boostUI[maxBoostCount];

	//�J����
	Camera* camera;
	
	//�{�X�V�[��
	BossScene* bossScene;
	//�T�E���h�N���X
	Sound* sound;

	//�Q�[���V�[���p�ϐ�
	//��]����
	int32_t rotationTimer;
	//�_�b�V���t���O
	bool isDash;
	bool isLeftDash;
	bool isRightDash;
	//�_�b�V������
	int32_t dashTimer;
	//�_�b�V���p�����A���O���ۑ�
	float initAngle;
	//�W�����v�㏸���x
	float jumpPower;
	//�W�����v�t���O
	bool isJump;
	//�e���˃N�[���^�C�}�[
	int32_t shotCoolTimer;
	//�e���˃t���O
	bool isShot;
	//�e��
	int32_t bulletCount;
	//HP
	int32_t hpCount;
	//�����[�h�t���O
	bool isReload;
	//�u�[�X�g�񕜃t���O
	bool isBoostReload;
	//�u�[�X�g�񕜎���
	float boostReloadTimer;
	//�u�[�X�g��
	int32_t boostCount;
	//�����[�h����
	int32_t reloadTimer;
	//���e�B�N�����W
	DirectX::XMFLOAT2 aimPos;
	//���e�B�N��3D���W
	Vector3 aim3dPos;
	//���[�J�����W
	Vector3 pos;
	//��]�p
	Vector3 rot;
	//�傫��
	Vector3 scale;
	//�v���C���[���[���h���W
	Vector3 playerWPos;
	//�J�����A���O��
	float cameraAngle;
	//�J�������W
	Vector3 cameraPos;
	//�_���[�W�t���O
	bool isDamage;
	//�_���[�W�^�C�}�[
	int32_t damageTimer;
	//���S�^�C�}�[
	int32_t deadTimer;
	//���S�t���O
	bool isDead;
};