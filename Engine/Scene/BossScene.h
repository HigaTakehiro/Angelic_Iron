#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "MotionMath.h"
#include "BossScenePlayer.h"
#include "PlayerBullet.h"
#include "Sound.h"
#include "BaseBoss.h"
#include "FirstBoss.h"
#include "Particle2d.h"

class BossScenePlayer;
class BaseBoss;
class FirstBoss;

class BossScene : public BaseScene
{
public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();
	/// <summary>
	/// �v���C���[�e��ǉ�
	/// </summary>
	void AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet);
	/// <summary>
	/// �{�X�e��ǉ�
	/// </summary>
	/// <param name="bossEnemy"></param>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> bosBullet);

private: //�����o�ϐ�

	//�r�����X�g
	std::list<std::unique_ptr<Object3d>> buildings;
	//�v���C���[�e���X�g
	std::list<std::unique_ptr<PlayerBullet>> playerBullets;
	//�{�X�e���X�g
	std::list<std::unique_ptr<EnemyBullet>> bossBullets;
	//2D�p�[�e�B�N�����X�g
	std::list<std::unique_ptr<Particle2d>> particles2d;
	//�J����
	Camera* camera = nullptr;
	//�T�E���h
	Sound* sound = nullptr;
	//�v���C���[
	BossScenePlayer* player = nullptr;
	//�n��
	Object3d* ground = nullptr;
	//�V��
	Object3d* celetialSphere = nullptr;
	//�|�X�g�G�t�F�N�g
	PostEffect* postEffect = nullptr;
	PostEffect::PostEffectNo postEffectNo;

	Vector3 groundPos = { 0, 0, 0 }; //�n�ʍ��W
	Vector3 groundScale = { 1, 1, 1 }; //�n�ʂ̑傫��
	Vector3 spherePos = { 0, 0, 0 }; //�V�����W
	Vector3 sphereScale = { 10, 10, 10 };  //�V���̑傫��

	Sprite* pause = nullptr;
	Sprite* titleBack = nullptr;
	Sprite* back = nullptr;

	//BaseBoss* boss;
	FirstBoss* firstBoss;

	XMFLOAT2 titleBackSize;
	XMFLOAT2 backSize;
	//�X�R�A
	int score;

	//�|�[�Y�t���O
	bool isPause;
	//�^�C�g���o�b�N�t���O
	bool isTitleBack;
	//���S�t���O
	bool isDead;
};

