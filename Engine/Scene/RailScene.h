#pragma once
#include "KeyInput.h"//
#include "DirectXSetting.h"//
#include "Object3d.h"
#include "Model.h"
#include "Sprite.h"
#include "DebugText.h"
#include "Sound.h"//
#include "Camera.h"
#include "MapChip.h"
#include "SafeDelete.h"
#include "FbxLoader.h"
#include "FBXObject3d.h"
#include "MouseInput.h"
#include "PadInput.h"
#include "Player.h"
#include "Collision.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "ModelManager.h"
#include "RailCamera.h"
#include "ImageManager.h"
#include "PostEffect.h"
#include "Particle2d.h"
#include "Bomb.h"
#include <sstream>
#include <chrono>
#include <thread>
#include "BaseScene.h"
#include "SceneManager.h"
#include "BaseEnemy.h"
#include "StraightEnemy.h"
#include "HomingEnemy.h"
#include "LightGroup.h"
#include "ParticleManager.h"
#include "TextDraw.h"

using namespace DirectX;
using namespace Microsoft::WRL;
class Player;

class RailScene : public BaseScene
{
private: //�ÓI�����o�ϐ�
	//�f�o�b�N�e�L�X�g�p�e�N�X�`���ԍ�
	static const int debugTextNumber = 0;

private: //�T�u�N���X
	enum FaceGraphics {
		OPE_NORMALFACE,
		OPE_SURPRISEFACE,
		OPE_SMILEFACE
	};

public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	RailScene() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~RailScene() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	/// <summary>
	/// �G�l�~�[�f�[�^�̓ǂݍ���
	/// </summary>
	void LoadEnemyData(const std::string filename);

	/// <summary>
	/// �ǂݍ��񂾃G�l�~�[�f�[�^�̍X�V
	/// </summary>
	void EnemyDataUpdate();

	/// <summary>
	/// ���[���J�����w��_���O���t�@�C������ǂݍ���
	/// </summary>
	void LoadRailPoint(const std::string filename);

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

	/// <summary>
	/// �G�e��ǉ�
	/// </summary>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet);

	/// <summary>
	/// �v���C���[�e��ǉ�
	/// </summary>
	void AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet);

	/// <summary>
	/// �{���̒e��ǉ�
	/// </summary>
	/// <param name="bomb"></param>
	void AddBomb(std::unique_ptr<Bomb> bomb);

	/// <summary>
	/// �G�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns></returns>
	std::list<std::unique_ptr<BaseEnemy>>& GetEnemyObj() { return enemies; }

private: //�����o�֐�

	/// <summary>
	/// string�^��wstring�^�ɕϊ�����(UTF-8)
	/// </summary>
	/// <param name="text">�ϊ��������e�L�X�g</param>
	/// <returns>wstring�^�̃e�L�X�g</returns>
	std::wstring StringToWstring(const std::string& text);

	/// <summary>
	/// ���b�N�I������������
	/// </summary>
	/// <param name="enemyPos">�G�̉�ʏ�̈ʒu</param>
	/// <param name="aimPos">�}�E�X�J�[�\���̈ʒu</param>
	/// <returns>�G�̈ʒu�ɃJ�[�\�������邩�ǂ���</returns>
	bool IsTargetCheck(XMFLOAT2 enemyPos, XMFLOAT2 aimPos);

private: //�ÓI�����o�ϐ�
	static const int32_t clearTime = 120;
	static const int32_t opeAnimeTime = 6;
	static const int32_t closeWindowTime = 120;
	static const int32_t openWindowTime = 120;

private: //�����o�ϐ�
	WinApp* winApp = nullptr; //�E�B���h�E�ݒ�N���X
	DebugText debugText; //�f�o�b�O�e�L�X�g�\���p�N���X
	Camera* camera = nullptr; //�J�����N���X
	MapChip* mapchip = nullptr; //�}�b�v�`�b�v�N���X
	RailCamera* railCamera = nullptr; //���[���J�����N���X
	PostEffect* postEffect = nullptr; //�|�X�g�G�t�F�N�g�N���X

	//�Q�[���I�u�W�F�N�g & �X�v���C�g
	Player* player = nullptr; //�v���C���[�N���X
	std::list<std::unique_ptr<BaseEnemy>> enemies;
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets; //�G�l�~�[�̒e���X�g
	std::list<std::unique_ptr<PlayerBullet>> playerBullets; //�v���C���[�̒e���X�g
	std::list<std::unique_ptr<Particle2d>> particles2d; //2d�p�[�e�B�N���̃��X�g
	std::list<std::unique_ptr<Bomb>> bombs; //�{���̒e���X�g
	std::list<std::unique_ptr<Object3d>> buildings; //�r�����X�g
	ParticleManager* bombParticle;
	ParticleManager* enemyParticle;
	ParticleManager* bulletParticle;
	Sprite* background = nullptr; //�w�i�摜
	Sprite* pause = nullptr;
	Sprite* titleBack = nullptr;
	Sprite* back = nullptr;
	Sprite* restart = nullptr;
	Sprite* scoreSprite = nullptr;
	Sprite* faceWindow = nullptr;
	Sprite* textWindow = nullptr;
	Sprite* opeNormal[3] = {};
	Sprite* opeSurprise[3] = {};
	Sprite* opeSmile[3] = {};
	Sprite* scoreNumber[6] = {};
	XMFLOAT2 titleBackSize;
	XMFLOAT2 backSize;
	XMFLOAT2 restartSize;
	XMFLOAT2 textWindowSize;
	XMFLOAT2 faceWindowSize;
	XMFLOAT2 operatorSize;

	Object3d* celetialSphere = nullptr; //�V���I�u�W�F�N�g
	Object3d* ground = nullptr; //�n�ʃI�u�W�F�N�g
	Vector3 groundPos = { 0, 0, 0 }; //�n�ʍ��W
	Vector3 groundScale = { 1, 1, 1 }; //�n�ʂ̑傫��
	Vector3 spherePos = { 0, 0, 0 }; //�V�����W
	Vector3 sphereScale = { 10, 10, 10 };  //�V���̑傫��
	LightGroup* light = nullptr;

	//�e�L�X�g�`��p�ϐ�
	TextDraw* textDraw = nullptr;
	int textSpeed;
	int textCount;
	int textAddTimer;

	//FBX�p�ϐ�
	FBXObject3d* object1 = nullptr; //FBX�e�X�g�I�u�W�F�N�g

	//�Q�[���V�[���p�ϐ�
	bool isDead; //�v���C���[���S�t���O
	bool isClear; //�N���A�V�[���t���O
	bool isWait; //�G�l�~�[�ǂݍ��ݑҋ@�t���O
	bool isMessageWait; //���b�Z�[�W�f�[�^�ǂݍ��ݑҋ@�t���O
	bool isTextDraw; //���b�Z�[�W�f�[�^�o�͊����t���O
	bool isPlayerDead; //�v���C���[���S�����o�p�t���O
	bool isPause; //�|�[�Y�t���O
	bool isTitleBack; //�^�C�g����ʕύX�t���O
	bool isTextWindowOpen; //���b�Z�[�W�E�B���h�E�I�[�v���t���O
	bool isRestart;
	int32_t waitTimer; //�G�l�~�[�ǂݍ��ݑҋ@����
	int32_t waitMessageTimer; //���b�Z�[�W�f�[�^�ǂݍ��ݑҋ@����
	int32_t clearTimer; //�N���A���o�p����
	int32_t closeWindowTimer; //�E�B���h�E������
	int32_t openWindowTimer; //�E�B���h�E�������
	std::stringstream enemyData; //�G�l�~�[�f�[�^�i�[�p������
	std::stringstream textData; //���b�Z�[�W�f�[�^�i�[�p������
	std::wstring drawMessage; //���b�Z�[�W���e�o�͗p������
	std::wstring message; //���b�Z�[�W���e�i�[������
	std::vector<Vector3> points; //���[���J�����p�X�v���C���w��_�i�[�R���e�i
	std::chrono::steady_clock::time_point referenceCount; //�X���[���o�p�Q�Ǝ���

	int score;
	int32_t opeAnimeTimer;
	int opeAnimeCount;
	FaceGraphics faceType;

	PostEffect::PostEffectNo postEffectNo;
};

