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
#include "Sound.h"
#include "ImageManager.h"
#include "Bomb.h"
#include "BaseEnemy.h"
#include "RailScene.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class RailScene;
class BaseEnemy;

class Player
{
public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(Camera* camera, Sound* sound, float clearTime);

	/// <summary>
	/// �v���C���[
	/// </summary>
	/// <param name="isClear">�N���A�t���O</param>
	/// <param name="clearTimer">�o�ߎ���</param>
	/// <param name="clearTime">�N���A���o����</param>
	void Update(bool isClear);

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
	const XMFLOAT3 GetPlayerPos() { return playerLPos; }

	/// <summary>
	/// 3D���e�B�N���̈ʒu�擾
	/// </summary>
	/// <returns></returns>
	const Vector3 Get3dAimPos() { return aimPos3d; }

	/// <summary>
	/// ���e�B�N���ʒu�擾
	/// </summary>
	/// <returns>����</returns>
	const XMFLOAT2 GetAimPos() { return aimPos; }

	/// <summary>
	/// �v���C���[�I�u�W�F�N�g�̎擾
	/// </summary>
	/// <returns>�v���C���[�I�u�W�F�N�g</returns>
	Object3d* GetPlayerObject() { return player; }

	/// <summary>
	/// �c��HP�擾
	/// </summary>
	/// <returns></returns>
	int GetHPCount() { return hpCount; }

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
	/// <param name="RailScene">�Q�[���V�[��</param>
	void SetRailScene(RailScene* RailScene) { this->railScene = RailScene; }

	///// <summary>
	///// �G�l�~�[���X�g���Z�b�g
	///// </summary>
	///// <param name="enemies"></param>
	//void SetEnemies(std::list<std::unique_ptr<Enemy>> enemies) { this->enemies; }

	/// <summary>
	/// �_���[�W�t���O�擾
	/// </summary>
	/// <returns>�_���[�W�t���O</returns>
	bool GetIsDamage() { return isDamage; }

	/// <summary>
	/// �{���t���O�擾
	/// </summary>
	/// <returns>�{���t���O</returns>
	bool GetIsBomb() { return isBomb; }

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
	/// �{���U������
	/// </summary>
	void BombShot();

	/// <summary>
	/// 3d���e�B�N���X�V����
	/// </summary>
	void AimUpdate();

	/// <summary>
	/// �_���[�W�G�t�F�N�g
	/// </summary>
	void DamageEffect();

	/// <summary>
	/// ���S���o
	/// </summary>
	void DeadPerformance();

	/// <summary>
	/// �N���A���o
	/// </summary>
	/// <param name="clearTimer">�N���A���o�o�ߎ���</param>
	/// <param name="clearTime">�N���A���o����</param>
	void ClearPerformance();

	/// <summary>
	/// �X�^�[�g���o
	/// </summary>
	void StartPerformance();

private: //�ÓI�����o�ϐ�
	//�ő�c�e��
	static const int maxBulletCount = 16;
	//�ő�HP
	static const int maxHp = 3;
	//�����[�h����
	static const int reloadTime = 20;
	//�e���˃N�[���^�C��
	static const int shotCoolTime = 10;
	//�_���[�W�G�t�F�N�g��������
	static const int damageEffectTime = 40;
	//���S�����o�p����
	static const int32_t deadTime = 120;
	//�J�n�����o�p����
	static const int32_t startTime = 60;

private: //�����o�ϐ�
	Vector3 playerLPos = { 0, 0, 0 };
	Vector3 playerWPos = { 0, 0, 0 };
	Vector3 playerRot = { 0, 0, 0 };
	Vector3 playerScale = { 0, 0, 0 };

	Object3d* player = nullptr;
	Object3d* aim3d = nullptr;
	Object3d* gun = nullptr;
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
	RailScene* railScene;
	Sound* sound;
	//std::list<std::unique_ptr<Enemy>> enemies;

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
	//���S�����o�p����
	int32_t deadTimer;
	//�C�[�W���O���Ԍv���p�z��
	float holdTimer[4];
	//�C�[�W���O�p���Ԍv��
	float returnTimer;
	//�N���A���o�p���Ԍv��
	float clearTimer;
	//�N���A����
	float clearTime;
	//�X�^�[�g���o�p���Ԍv��
	int32_t startTimer;
	//�X�^�[�g�t���O
	bool isStart;
	//�{���t���O
	bool isBomb;
};

