#pragma once
#include "KeyInput.h"
#include "Object3d.h"
#include "Model.h"
#include "MouseInput.h"
#include "PadInput.h"
#include "Sprite.h"
#include "Vector3.h"
#include "Camera.h"
#include "DebugText.h"
#include "WinApp.h"
#include "PlayerBullet.h"
#include <memory>
#include "Vector3.h"
#include "MatCalc.h"
#include "ModelManager.h"
#include "PlayerBullet.h"
#include "GameScene.h"
#include "Sound.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class GameScene;

class Player
{
public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(Camera* camera, Sound* sound);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	/// <summary>
	/// �X�v���C�g�`�揈��
	/// </summary>
	void SpriteDraw();

	/// <summary>
	/// 3D�I�u�W�F�N�g�`�揈��
	/// </summary>
	void ObjectDraw();

	/// <summary>
	/// �ʒu�擾
	/// </summary>
	/// <returns>�ʒu</returns>
	const XMFLOAT3 GetPlayerPos() { return playerWPos; }

	/// <summary>
	/// 3D���e�B�N���̈ʒu�擾
	/// </summary>
	/// <returns></returns>
	const Vector3 GetAimPos() { return aimPos3d; }

	/// <summary>
	/// �����擾
	/// </summary>
	/// <returns>����</returns>
	const XMFLOAT2 GetPlayerRot() { return aimPos; }

	/// <summary>
	/// �v���C���[�I�u�W�F�N�g�̎擾
	/// </summary>
	/// <returns>�v���C���[�I�u�W�F�N�g</returns>
	Object3d* GetPlayerObject() { return player; }

	/// <summary>
	/// ���S�t���O�擾
	/// </summary>
	/// <returns>���S�t���O</returns>
	bool GetIsDead() { return isDead; }

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	void OnCollision();

	/// <summary>
	/// ���Z�b�g����
	/// </summary>
	void Reset();

	/// <summary>
	/// �Q�[���V�[�����Z�b�g
	/// </summary>
	/// <param name="gameScene">�Q�[���V�[��</param>
	void SetGameScene(GameScene* gameScene) { this->gameScene = gameScene; }

	/// <summary>
	/// �_���[�W�t���O�擾
	/// </summary>
	/// <returns>�_���[�W�t���O</returns>
	bool GetIsDamage() { return isDamage; }

private: //�����o�֐�
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// �ʏ�U������
	/// </summary>
	void Shot();

	/// <summary>
	/// 3d���e�B�N���X�V����
	/// </summary>
	void AimUpdate();

	/// <summary>
	/// �_���[�W�G�t�F�N�g
	/// </summary>
	void DamageEffect();


private: //�ÓI�����o�ϐ�
	//�ő�c�e��
	static const int maxBulletCount = 16;
	//�ő�HP
	static const int maxHp = 3;
	//�����[�h����
	static const int reloadTime = 60;
	//�e���˃N�[���^�C��
	static const int shotCoolTime = 10;
	//�_���[�W�G�t�F�N�g��������
	static const int damageEffectTime = 20;

private: //�����o�ϐ�
	Vector3 playerLPos = { 0, 0, 0 };
	Vector3 playerWPos = { 0, 0, 0 };
	Vector3 playerRot = { 0, 0, 0 };
	Vector3 playerScale = { 0, 0, 0 };

	Object3d* player = nullptr;
	Object3d* aim3d = nullptr;
	Sprite* aim = nullptr;
	Sprite* playerUI = nullptr;
	Sprite* hpUI[maxHp];
	Sprite* bulletUI[maxBulletCount];
	Sprite* reloadUI = nullptr;

	bool isShot = false;
	bool isDead = false;
	//�Q�[���V�[���p�ϐ�
	XMFLOAT2 aimPos;
	Vector3 oldShotPos;
	Vector3 targetAimPos;
	XMVECTOR positionRaticle;
	XMMATRIX matViewPort;
	XMMATRIX matViewProjection;
	XMFLOAT3 aimPosMath;

	Vector3 aimPos3d;
	Camera* camera;
	GameScene* gameScene;
	Sound* sound;

	//�c�e��
	int bulletCount;
	//HP
	int hpCount;
	//�����[�h����
	int reloadTimer;
	//�e���˃N�[���^�C��
	int shotCoolTimer;
	//�����[�h�t���O
	bool isReload = false;
	//�_���[�W�G�t�F�N�g����
	int damageEffectTimer;
	//�_���[�W�G�t�F�N�g�p�t���O
	bool isDamage = false;
};

