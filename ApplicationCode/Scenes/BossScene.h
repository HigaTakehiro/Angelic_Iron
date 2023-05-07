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
#include "TextDraw.h"
#include <fstream>

class BossScenePlayer;
class BaseBoss;
class FirstBoss;

class BossScene : public BaseScene
{
public: //�T�u�N���X
	enum class FaceGraphics {
		OPE_NORMALFACE,
		OPE_SURPRISEFACE,
		OPE_SMILEFACE
	};

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

	/// <summary>
	/// ��b�f�[�^�̓ǂݍ���
	/// </summary>
	/// <param name="fileName"></param>
	void LoadTextMessage(const std::string fileName);

	/// <summary>
	/// �ǂݍ��񂾃e�L�X�g�f�[�^�̍X�V
	/// </summary>
	void TextMessageUpdate();

	/// <summary>
	/// �e�L�X�g�f�[�^�̕`��
	/// </summary>
	void TextMessageDraw();

private: //�����o�֐�
	/// <summary>
	/// string�^��wstring�^�ɕϊ�����(UTF-8)
	/// </summary>
	/// <param name="text">�ϊ��������e�L�X�g</param>
	/// <returns>wstring�^�̃e�L�X�g</returns>
	std::wstring StringToWstring(const std::string& text);

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
	//�v���C���[�e���X�g
	std::list<std::unique_ptr<PlayerBullet>> playerBullets_;
	//�{�X�e���X�g
	std::list<std::unique_ptr<EnemyBullet>> bossBullets_;
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
	FaceGraphics faceType_;

	Vector3 groundPos_ = { 0, 0, 0 }; //�n�ʍ��W
	Vector3 groundScale_ = { 1, 1, 1 }; //�n�ʂ̑傫��
	Vector3 spherePos_ = { 0, 0, 0 }; //�V�����W
	Vector3 sphereScale_ = { 10, 10, 10 };  //�V���̑傫��

	Sprite* pause_ = nullptr;
	Sprite* titleBack_ = nullptr;
	Sprite* back_ = nullptr;
	Sprite* scoreText_ = nullptr;
	Sprite* scoreNumber_[6] = {};
	//�e�L�X�g�p�ϐ�
	Sprite* faceWindow_ = nullptr;
	Sprite* textWindow_ = nullptr;
	Sprite* opeNormal_[3] = {};
	Sprite* opeSurprise_[3] = {};
	Sprite* opeSmile_[3] = {};
	Sprite* movieBar_[2] = {};
	DirectX::XMFLOAT2 textWindowSize_;
	DirectX::XMFLOAT2 faceWindowSize_;
	DirectX::XMFLOAT2 operatorSize_;
	DirectX::XMFLOAT2 movieBarPos_[2] = {};

	TextDraw* textDraw_ = nullptr;
	int32_t textSpeed_;
	int32_t textCount_;
	int32_t textAddTimer_;

	int32_t closeWindowTimer_; //�E�B���h�E������
	int32_t openWindowTimer_; //�E�B���h�E�������
	int32_t movieTimer_; //���[�r�[����

	Vector3 cameraPos_; //�J�������W

	bool isMessageWait_; //���b�Z�[�W�f�[�^�ǂݍ��ݑҋ@�t���O
	bool isTextWindowOpen_; //�e�L�X�g�E�B���h�E�I�[�v���t���O
	int32_t waitMessageTimer_; //���b�Z�[�W�f�[�^�ǂݍ��ݑҋ@����
	bool isTextDraw_; //���b�Z�[�W�f�[�^�o�͊����t���O

	std::stringstream textData_; //���b�Z�[�W�f�[�^�i�[�p������
	std::wstring drawMessage_; //���b�Z�[�W���e�o�͗p������
	std::wstring message_; //���b�Z�[�W���e�i�[������

	int32_t opeAnimeTimer_;
	int32_t opeAnimeCount_;

	//BaseBoss* boss;
	FirstBoss* firstBoss_;

	DirectX::XMFLOAT2 titleBackSize_;
	DirectX::XMFLOAT2 backSize_;
	//�X�R�A
	int32_t score_;

	//�|�[�Y�t���O
	bool isPause_;
	//�^�C�g���o�b�N�t���O
	bool isTitleBack_;
	//���S�t���O
	bool isDead_;
};