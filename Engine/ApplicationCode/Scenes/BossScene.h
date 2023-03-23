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
	enum FaceGraphics {
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
	int postEffectTime;
	//���C�g
	LightGroup* light = nullptr;
	FaceGraphics faceType;

	Vector3 groundPos = { 0, 0, 0 }; //�n�ʍ��W
	Vector3 groundScale = { 1, 1, 1 }; //�n�ʂ̑傫��
	Vector3 spherePos = { 0, 0, 0 }; //�V�����W
	Vector3 sphereScale = { 10, 10, 10 };  //�V���̑傫��

	Sprite* pause = nullptr;
	Sprite* titleBack = nullptr;
	Sprite* back = nullptr;
	Sprite* scoreText = nullptr;
	Sprite* scoreNumber[6] = {};
	//�e�L�X�g�p�ϐ�
	Sprite* faceWindow = nullptr;
	Sprite* textWindow = nullptr;
	Sprite* opeNormal[3] = {};
	Sprite* opeSurprise[3] = {};
	Sprite* opeSmile[3] = {};
	DirectX::XMFLOAT2 textWindowSize;
	DirectX::XMFLOAT2 faceWindowSize;
	DirectX::XMFLOAT2 operatorSize;

	TextDraw* textDraw = nullptr;
	int textSpeed;
	int textCount;
	int textAddTimer;

	int32_t closeWindowTimer; //�E�B���h�E������
	int32_t openWindowTimer; //�E�B���h�E�������
	int32_t movieTimer; //���[�r�[����

	Vector3 cameraPos; //�J�������W

	bool isMessageWait; //���b�Z�[�W�f�[�^�ǂݍ��ݑҋ@�t���O
	bool isTextWindowOpen; //�e�L�X�g�E�B���h�E�I�[�v���t���O
	int32_t waitMessageTimer; //���b�Z�[�W�f�[�^�ǂݍ��ݑҋ@����
	bool isTextDraw; //���b�Z�[�W�f�[�^�o�͊����t���O

	std::stringstream textData; //���b�Z�[�W�f�[�^�i�[�p������
	std::wstring drawMessage; //���b�Z�[�W���e�o�͗p������
	std::wstring message; //���b�Z�[�W���e�i�[������

	int32_t opeAnimeTimer;
	int opeAnimeCount;

	//BaseBoss* boss;
	FirstBoss* firstBoss;

	DirectX::XMFLOAT2 titleBackSize;
	DirectX::XMFLOAT2 backSize;
	//�X�R�A
	int score;

	//�|�[�Y�t���O
	bool isPause;
	//�^�C�g���o�b�N�t���O
	bool isTitleBack;
	//���S�t���O
	bool isDead;
};

