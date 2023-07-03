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
#include "LightGroup.h"
#include "MessageWindow.h"
#include "BulletManager.h"
#include "Button.h"
#include <fstream>

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

private: //�����o�֐�

	/// <summary>
	/// �V�[���؂�ւ�����
	/// </summary>
	void SceneChange();

private: //�ÓI�����o�ϐ�
	static const int32_t opeAnimeTime = 6;
	static const int32_t closeWindowTime = 120;
	static const int32_t openWindowTime = 120;

private: //�����o�ϐ�

	//�r�����X�g
	std::list<std::unique_ptr<Object3d>> buildings_;
	BulletManager* bulletManager_;
	//2D�p�[�e�B�N�����X�g
	std::list<std::unique_ptr<Particle2d>> particles2d_;
	//�J����
	Camera* camera_ = nullptr;
	//�T�E���h
	Sound* sound_ = nullptr;
	//�v���C���[
	BossScenePlayer* player_ = nullptr;
	//�n��
	Object3d* ground_ = nullptr;
	//�V��
	Object3d* celetialSphere_ = nullptr;
	//�|�X�g�G�t�F�N�g
	PostEffect* postEffect_ = nullptr;
	PostEffect::PostEffectNo postEffectNo_;
	int32_t postEffectTime_;
	//���C�g
	LightGroup* light_ = nullptr;

	Vector3 groundPos_ = { 0, 0, 0 }; //�n�ʍ��W
	Vector3 groundScale_ = { 1, 1, 1 }; //�n�ʂ̑傫��
	Vector3 spherePos_ = { 0, 0, 0 }; //�V�����W
	Vector3 sphereScale_ = { 10, 10, 10 };  //�V���̑傫��

	Sprite* pause_ = nullptr;
	Button* titleBack_ = nullptr;
	Button* back_ = nullptr;
	Sprite* scoreText_ = nullptr;
	Sprite* scoreNumber_[6] = {};
	//�e�L�X�g�p�ϐ�
	Sprite* movieBar_[2] = {};
	DirectX::XMFLOAT2 movieBarPos_[2] = {};
	//���b�Z�[�W�E�B���h�E
	MessageWindow* messageWindow_;

	int32_t movieTimer_; //���[�r�[����

	Vector3 cameraPos_; //�J�������W

	//BaseBoss* boss;
	FirstBoss* firstBoss_;

	//�X�R�A
	int32_t score_;
	//�^�C�g����ʃo�b�N�t���O
	bool isTitleBack_;
	//�|�[�Y�t���O
	bool isPause_;
	//���S�t���O
	bool isDead_;
};