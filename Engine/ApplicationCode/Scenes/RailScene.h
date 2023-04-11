#pragma once
#include "Object3d.h"
#include "Sprite.h"
#include "DebugText.h"
#include "Camera.h"
#include "FBXObject3d.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "RailCamera.h"
#include "PostEffect.h"
#include "Particle2d.h"
#include "Bomb.h"
#include <sstream>
#include <thread>
#include "BaseScene.h"
#include "BaseEnemy.h"
#include "LightGroup.h"
#include "ParticleManager.h"
#include "TextDraw.h"
#include "BulletCase.h"

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
	/// �ǂݍ��񂾃G�l�~�[�f�[�^�̍X�V
	/// </summary>
	void EnemyDataUpdate();

	/// <summary>
	/// ���[���J�����w��_���O���t�@�C������ǂݍ���
	/// </summary>
	void LoadRailPoint(const std::string& filename);

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
	/// ��䰂�ǉ�
	/// </summary>
	/// <param name="bulletCase">���</param>
	void AddBulletCase(std::unique_ptr<BulletCase> bulletCase);

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
	/// ���b�N�I������������
	/// </summary>
	/// <param name="enemyPos">�G�̉�ʏ�̈ʒu</param>
	/// <param name="aimPos">�}�E�X�J�[�\���̈ʒu</param>
	/// <returns>�G�̈ʒu�ɃJ�[�\�������邩�ǂ���</returns>
	bool IsTargetCheck(DirectX::XMFLOAT2 enemyPos, DirectX::XMFLOAT2 aimPos);

	/// <summary>
	/// �X���[�ɂ���X�V����
	/// </summary>
	void DelayUpdates();

	/// <summary>
	/// ���[���V���[�e�B���O�p�[�g�N���A���o
	/// </summary>
	void ClearPaformance();

	/// <summary>
	/// �����蔻��`�F�b�N
	/// </summary>
	void CollisionCheck();

	/// <summary>
	/// �G�֘A�̍X�V����
	/// </summary>
	/// <param name="enemy"></param>
	void EnemyReactions(BaseEnemy* enemy);

	/// <summary>
	/// �G�t�F�N�g��������
	/// </summary>
	void AddEffect();

	/// <summary>
	/// �|�[�Y���X�V����
	/// </summary>
	void Pause();

	/// <summary>
	/// �`���[�g���A������
	/// </summary>
	void Tutorial();

private: //�����o�֐�
	/// <summary>
	/// �V�[���؂�ւ�����
	/// </summary>
	void SceneChange();

private: //�ÓI�����o�ϐ�
	//�N���A���o�p����
	static const int32_t clearTime = 120;
	//��O���t�B�b�N�A�j���[�V��������
	static const int32_t faceAnimeTime = 6;
	//�e�L�X�g�E�B���h�E������
	static const int32_t closeWindowTime = 120;
	//�e�L�X�g�E�B���h�E�J������
	static const int32_t openWindowTime = 120;
	//�Q�[���I�[�o�[����HP
	static const int noneHP = 0;

private: //�����o�ϐ�
	//�E�B���h�E�ݒ�N���X
	WinApp* winApp = nullptr;
	//�f�o�b�O�e�L�X�g�\���p�N���X
	DebugText debugText;
	//�J�����N���X
	Camera* camera = nullptr;
	//���[���J�����N���X
	RailCamera* railCamera = nullptr;
	//�|�X�g�G�t�F�N�g�N���X
	PostEffect* postEffect = nullptr;

	//�Q�[���I�u�W�F�N�g & �X�v���C�g
	//�v���C���[�N���X
	Player* player = nullptr;
	//�G���X�g
	std::list<std::unique_ptr<BaseEnemy>> enemies;
	//�G�l�~�[�̒e���X�g
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets;
	//�v���C���[�̒e���X�g
	std::list<std::unique_ptr<PlayerBullet>> playerBullets;
	//2d�p�[�e�B�N���̃��X�g
	std::list<std::unique_ptr<Particle2d>> particles2d;
	//�{���̒e���X�g
	std::list<std::unique_ptr<Bomb>> bombs;
	//��䰃��X�g
	std::list<std::unique_ptr<BulletCase>> bulletCases;
	//�r�����X�g
	std::list<std::unique_ptr<Object3d>> buildings;
	//�{���p�p�[�e�B�N��
	ParticleManager* bombParticle;
	//�G�p�p�[�e�B�N��
	ParticleManager* enemyParticle;
	//�}�Y���t���b�V���p�p�[�e�B�N��
	ParticleManager* gunParticle;
	//�X���X�^�[�p�p�[�e�B�N��
	ParticleManager* thrusterParticle;
	//�|�[�Y�e�L�X�g
	Sprite* pause = nullptr;
	//�^�C�g���o�b�N�{�^��
	Sprite* titleBack = nullptr;
	//�|�[�Y��ʃN���[�Y�{�^��
	Sprite* back = nullptr;
	//���X�^�[�g�{�^��
	Sprite* restart = nullptr;
	//�X�R�A�e�L�X�g
	Sprite* scoreSprite = nullptr;
	//��O���t�B�b�N�E�B���h�E
	Sprite* faceWindow = nullptr;
	//�e�L�X�g�E�B���h�E
	Sprite* textWindow = nullptr;
	//�I�y���[�^�[�ʏ�t�F�C�X
	Sprite* opeNormal[3] = {};
	//�I�y���[�^�[�����t�F�C�X
	Sprite* opeSurprise[3] = {};
	//�I�y���[�^�[�Ί�t�F�C�X
	Sprite* opeSmile[3] = {};
	//�X�R�A����
	Sprite* scoreNumber[6] = {};
	//�`���[�g���A���A�C�R��
	Sprite* how_to_up_;
	Sprite* how_to_down_;
	Sprite* how_to_left_;
	Sprite* how_to_right_;
	Sprite* how_to_shot_;
	//�^�C�g���o�b�N�{�^���T�C�Y
	DirectX::XMFLOAT2 titleBackSize;
	//�|�[�Y��ʃN���[�Y�{�^���T�C�Y
	DirectX::XMFLOAT2 backSize;
	//���X�^�[�g�{�^���T�C�Y
	DirectX::XMFLOAT2 restartSize;
	//�e�L�X�g�E�B���h�E�T�C�Y
	DirectX::XMFLOAT2 textWindowSize;
	//��O���t�B�b�N�E�B���h�E�T�C�Y
	DirectX::XMFLOAT2 faceWindowSize;
	//��O���t�B�b�N�T�C�Y
	DirectX::XMFLOAT2 faceGraphicSize;

	//�V���I�u�W�F�N�g
	Object3d* celetialSphere = nullptr;
	//�n�ʃI�u�W�F�N�g
	Object3d* ground = nullptr;
	//�n�ʍ��W
	Vector3 groundPos = { 0, 0, 0 };
	//�n�ʂ̑傫��
	Vector3 groundScale = { 1, 1, 1 };
	//�V�����W
	Vector3 spherePos = { 0, 0, 0 };
	//�V���̑傫��
	Vector3 sphereScale = { 10, 10, 10 };
	//���C�g�I�u�W�F�N�g
	LightGroup* light = nullptr;

	//�e�L�X�g�`��p�ϐ�
	//DirectWrite�e�L�X�g�`��N���X
	TextDraw* textDraw = nullptr;
	//�e�L�X�g�X�s�[�h
	int textSpeed;
	//�e�L�X�g��
	int textCount;
	//�e�L�X�g�ǉ�����
	int textAddTimer;

	//�Q�[���V�[���p�ϐ�
	//�v���C���[���S�t���O
	bool isDead;
	//�N���A�V�[���t���O
	bool isClear;
	//�G�l�~�[�ǂݍ��ݑҋ@�t���O
	bool isWait;
	//���b�Z�[�W�f�[�^�ǂݍ��ݑҋ@�t���O
	bool isMessageWait;
	//���b�Z�[�W�f�[�^�o�͊����t���O
	bool isTextDrawComplete;
	//�v���C���[���S�����o�p�t���O
	bool isPlayerDead;
	//�|�[�Y�t���O
	bool isPause;
	//�^�C�g����ʕύX�t���O
	bool isTitleBack;
	//���b�Z�[�W�E�B���h�E�I�[�v���t���O
	bool isTextWindowOpen;
	//���X�^�[�g�t���O
	bool isRestart;
	//�`���[�g���A�������t���O
	bool isMoveUp_;
	bool isMoveDown_;
	bool isMoveLeft_;
	bool isMoveRight_;
	bool isShot_;
	//�`���[�g���A���A�C�R���A���t�@�l
	float how_to_up_alpha_;
	float how_to_down_alpha_;
	float how_to_left_alpha_;
	float how_to_right_alpha_;
	float how_to_shot_alpha_;
	//�G�l�~�[�ǂݍ��ݑҋ@����
	int32_t waitTimer;
	//���b�Z�[�W�f�[�^�ǂݍ��ݑҋ@����
	int32_t waitMessageTimer;
	//�N���A���o�p����
	int32_t clearTimer;
	//�E�B���h�E������
	int32_t closeWindowTimer;
	//�E�B���h�E�������
	int32_t openWindowTimer;
	//�G�l�~�[�f�[�^�i�[�p������
	std::stringstream enemyData;
	//���b�Z�[�W�f�[�^�i�[�p������
	std::stringstream textData;
	//���b�Z�[�W���e�o�͗p������
	std::wstring drawMessage;
	//���b�Z�[�W���e�i�[������
	std::wstring message;
	//���[���J�����p�X�v���C���w��_�i�[�R���e�i
	std::vector<Vector3> points;
	//�X�R�A
	int score;
	//��O���t�B�b�N�A�j���[�V�����^�C�}�[
	int32_t faceAnimeTimer;
	//��O���t�B�b�N�A�j���[�V�����ԍ�
	int faceAnimeCount;
	//��O���t�B�b�N�^�C�v
	FaceGraphics faceType;
	//�X���[���o�p�^�C�}�[
	int32_t delayTimer;
	//�|�X�g�G�t�F�N�g�ԍ�
	PostEffect::PostEffectNo postEffectNo;
};

