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
#include "ModelManager.h"
#include "PlayerBullet.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "Bomb.h"
#include "BaseEnemy.h"
#include "RailScene.h"
#include "ParticleManager.h"
#include "BulletCase.h"
#include "BulletManager.h"
#include "KeyInputHandler.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class BaseEnemy;
class KeyInputHandler;

class Player
{
public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(Camera* camera, float clearTime);

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
	const XMFLOAT3 GetPlayerPos() { return playerLPos_; }

	/// <summary>
	/// �e�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�e�I�u�W�F�N�g</returns>
	Object3d* GetGunObject() { return gun_; }

	/// <summary>
	/// 3D���e�B�N���̈ʒu�擾
	/// </summary>
	/// <returns></returns>
	const Vector3 Get3dAimPos() { return aimPos3d_; }

	/// <summary>
	/// ���e�B�N���ʒu�擾
	/// </summary>
	/// <returns>����</returns>
	const XMFLOAT2 GetAimPos() { return aimPos_; }

	/// <summary>
	/// �v���C���[�I�u�W�F�N�g�̎擾
	/// </summary>
	/// <returns>�v���C���[�I�u�W�F�N�g</returns>
	Object3d* GetPlayerObject() { return player_; }

	/// <summary>
	/// �c��HP�擾
	/// </summary>
	/// <returns></returns>
	int32_t GetHPCount() { return hpCount_; }

	/// <summary>
	/// ���S�t���O�擾
	/// </summary>
	/// <returns>���S�t���O</returns>
	bool GetIsDead() { return isDead_; }

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
	void SetRailScene(RailScene* RailScene) { railScene_ = RailScene; }

	/// <summary>
	/// �e�}�l�[�W���[���Z�b�g
	/// </summary>
	/// <param name="bulletManager">�e�}�l�[�W���[</param>
	void SetBulletManager(BulletManager* bulletManager) { bulletManager_ = bulletManager; }

	/// <summary>
	/// �N���A���o�ŏI�n�_���Z�b�g
	/// </summary>
	/// <param name="clearPos">�N���A���o�ŏI�n�_</param>
	void SetClearPos(const Vector3 clearPos) { clearPos_ = clearPos; }

	/// <summary>
	/// ���ˈʒu���Z�b�g
	/// </summary>
	/// <param name="shotDistance"></param>
	void SetShotDistance(const float shotDistance) { shotDistance_ = shotDistance; }

	/// <summary>
	/// �v���C���[���W�Ƀx�N�g�������Z
	/// </summary>
	/// <param name="vector">�x�N�g��</param>
	void AddPlayerVector(const Vector3 vector) { playerLPos_ += vector; }

	/// <summary>
	/// �_���[�W�t���O�擾
	/// </summary>
	/// <returns>�_���[�W�t���O</returns>
	bool GetIsDamage() { return isDamage_; }

	/// <summary>
	/// �{���t���O�擾
	/// </summary>
	/// <returns>�{���t���O</returns>
	bool GetIsBomb() { return isBomb_; }

	/// <summary>
	/// �{���U���^�C�}�[�擾
	/// </summary>
	/// <returns>�{���U��</returns>
	int32_t GetBombTimer() { return bombTimer_; }

	/// <summary>
	/// ���˃t���O�擾
	/// </summary>
	/// <returns>���˃t���O</returns>
	bool GetIsShot() { return isShot_; }

	/// <summary>
	/// �ʏ�U������
	/// </summary>
	void Shot();

	/// <summary>
	/// �{�����[�h�ɐ؂�ւ���
	/// </summary>
	void SetBombMode();

	/// <summary>
	/// �����[�h����
	/// </summary>
	void Reload();

	/// <summary>
	/// �{���U������
	/// </summary>
	void BombShot();

private: //�����o�֐�

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

	/// <summary>
	/// �v���C���[�ʒu�␳
	/// </summary>
	void PlayerPosCorrection();

	/// <summary>
	/// �{���U�����x�N�g����������
	/// </summary>
	/// <param name="enemyCount">�^�[�Q�b�g���Ă���G�̐�</param>
	/// <returns>�x�N�g������</returns>
	XMVECTOR BombVectorDirectionJudge(const int32_t enemyCount);

private: //�ÓI�����o�ϐ�
	//�ő�c�e��
	static const int32_t maxBulletCount = 16;
	//�ő�HP
	static const int32_t maxHp = 3;
	//�����[�h����
	static const int32_t reloadTime = 60;
	//�e���˃N�[���^�C��
	static const int32_t shotCoolTime = 10;
	//�_���[�W�G�t�F�N�g��������
	static const int32_t damageEffectTime = 40;
	//���S�����o�p����
	static const int32_t deadTime = 120;
	//�J�n�����o�p����
	static const int32_t startTime = 60;
	//�{���U���^�C�}�[
	static const int32_t bombTime = 60 * 5;
	//�e�����Ȃ����
	static const int32_t noneBulletCount = 0;
	//�ړ����x
	static const float moveSpeed;

private: //�����o�ϐ�
	Vector3 playerLPos_ = { 0, 0, 0 };
	Vector3 playerWPos_ = { 0, 0, 0 };
	Vector3 playerRot_ = { 0, 0, 0 };
	Vector3 playerScale_ = { 0, 0, 0 };
	Vector3 clearPos_ = {0.0f, 0.0f, 0.0f};

	Object3d* player_ = nullptr;
	Object3d* gun_ = nullptr;
	Sprite* playerUI_ = nullptr;
	Sprite* hpUI_[maxHp];
	Sprite* bulletUI_[maxBulletCount];
	Sprite* reloadUI_ = nullptr;
	Sprite* bomb_[3] = {};

	bool isShot_ = false;
	bool isDead_ = false;
	//�Q�[���V�[���p�ϐ�
	XMFLOAT2 aimPos_;
	Vector3 oldShotPos_;
	Vector3 targetAimPos_;
	XMVECTOR positionRaticle_;
	XMMATRIX matViewPort_;
	XMMATRIX matViewProjection_;
	XMFLOAT3 aimPosMath_;

	Vector3 aimPos3d_;
	Camera* camera_;
	RailScene* railScene_;
	BulletManager* bulletManager_;

	//�c�e��
	int32_t bulletCount_;
	//HP
	int32_t hpCount_;
	//�����[�h����
	int32_t reloadTimer_;
	//�e���˃N�[���^�C��
	int32_t shotCoolTimer_;
	//�{���U���^�C�}�[
	int32_t bombTimer_;
	//�����[�h�t���O
	bool isReload_ = false;
	//�_���[�W�G�t�F�N�g����
	int32_t damageEffectTimer_;
	//�_���[�W�G�t�F�N�g�p�t���O
	bool isDamage_ = false;
	//���S�����o�p����
	int32_t deadTimer_;
	//�C�[�W���O���Ԍv���p�z��
	float holdTimer_[4];
	//�C�[�W���O�p���Ԍv��
	float returnTimer_;
	//�N���A���o�p���Ԍv��
	float clearTimer_;
	//�N���A����
	float clearTime_;
	//�X�^�[�g���o�p���Ԍv��
	int32_t startTimer_;
	//�X�^�[�g�t���O
	bool isStart_;
	//�{���t���O
	bool isBomb_;
	//�{����
	int32_t bombCount_;
	//���ˈʒu
	float shotDistance_;
	//�R���g���[���[
	KeyInputHandler* controller_;
};