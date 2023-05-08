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
#include "JsonLoader.h"

class Player;

class RailScene : public BaseScene
{
private: //�ÓI�����o�ϐ�
	//�f�o�b�N�e�L�X�g�p�e�N�X�`���ԍ�
	static const int32_t debugTextNumber = 0;

private: //�T�u�N���X
	enum class FaceGraphics {
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
	std::list<std::unique_ptr<BaseEnemy>>& GetEnemyObj() { return enemies_; }

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

	/// <summary>
	/// �{���U�����o
	/// </summary>
	void BombPerformance();

	/// <summary>
	/// �{���U���G�t�F�N�g
	/// </summary>
	void BombHitEffect(Bomb* bomb);

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
	static const int32_t noneHP = 0;
	//�{���U������
	static const int32_t bombTime = 60 * 5;

private: //�����o�ϐ�
	//�E�B���h�E�ݒ�N���X
	WinApp* winApp_ = nullptr;
	//�f�o�b�O�e�L�X�g�\���p�N���X
	DebugText debugText_;
	//�J�����N���X
	Camera* camera_ = nullptr;
	//���[���J�����N���X
	RailCamera* railCamera_ = nullptr;
	//�|�X�g�G�t�F�N�g�N���X
	PostEffect* postEffect_ = nullptr;

	//�Q�[���I�u�W�F�N�g & �X�v���C�g
	//�v���C���[�N���X
	Player* player_ = nullptr;
	//�G���X�g
	std::list<std::unique_ptr<BaseEnemy>> enemies_;
	//�G�l�~�[�̒e���X�g
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	//�v���C���[�̒e���X�g
	std::list<std::unique_ptr<PlayerBullet>> playerBullets_;
	//2d�p�[�e�B�N���̃��X�g
	std::list<std::unique_ptr<Particle2d>> particles2d_;
	//�{���̒e���X�g
	std::list<std::unique_ptr<Bomb>> bombs_;
	//��䰃��X�g
	std::list<std::unique_ptr<BulletCase>> bulletCases_;
	//json���[�_�[
	std::unique_ptr<JsonLoader> jsonLoader_;
	//�{���p�p�[�e�B�N��
	ParticleManager* bombParticle_;
	//�G�p�p�[�e�B�N��
	ParticleManager* enemyParticle_;
	//�}�Y���t���b�V���p�p�[�e�B�N��
	ParticleManager* gunParticle_;
	//�X���X�^�[�p�p�[�e�B�N��
	ParticleManager* thrusterParticle_;
	//�|�[�Y�e�L�X�g
	Sprite* pause_ = nullptr;
	//�^�C�g���o�b�N�{�^��
	Sprite* titleBack_ = nullptr;
	//�|�[�Y��ʃN���[�Y�{�^��
	Sprite* back_ = nullptr;
	//���X�^�[�g�{�^��
	Sprite* restart_ = nullptr;
	//�X�R�A�e�L�X�g
	Sprite* scoreSprite_ = nullptr;
	//��O���t�B�b�N�E�B���h�E
	Sprite* faceWindow_ = nullptr;
	//�e�L�X�g�E�B���h�E
	Sprite* textWindow_ = nullptr;
	//�I�y���[�^�[�ʏ�t�F�C�X
	Sprite* opeNormal_[3] = {};
	//�I�y���[�^�[�����t�F�C�X
	Sprite* opeSurprise_[3] = {};
	//�I�y���[�^�[�Ί�t�F�C�X
	Sprite* opeSmile_[3] = {};
	//�X�R�A����
	Sprite* scoreNumber_[6] = {};
	//�{���U���^�C�}�[����
	Sprite* bombTimerNumber_[3] = {};
	//�`���[�g���A���A�C�R��
	Sprite* how_to_up_;
	Sprite* how_to_down_;
	Sprite* how_to_left_;
	Sprite* how_to_right_;
	Sprite* how_to_shot_;
	Sprite* how_to_bomb_;
	//�^�C�g���o�b�N�{�^���T�C�Y
	DirectX::XMFLOAT2 titleBackSize_;
	//�|�[�Y��ʃN���[�Y�{�^���T�C�Y
	DirectX::XMFLOAT2 backSize_;
	//���X�^�[�g�{�^���T�C�Y
	DirectX::XMFLOAT2 restartSize_;
	//�e�L�X�g�E�B���h�E�T�C�Y
	DirectX::XMFLOAT2 textWindowSize_;
	//��O���t�B�b�N�E�B���h�E�T�C�Y
	DirectX::XMFLOAT2 faceWindowSize_;
	//��O���t�B�b�N�T�C�Y
	DirectX::XMFLOAT2 faceGraphicSize_;

	//���C�g�I�u�W�F�N�g
	LightGroup* light_ = nullptr;

	//�e�L�X�g�`��p�ϐ�
	//DirectWrite�e�L�X�g�`��N���X
	TextDraw* textDraw_ = nullptr;
	//�e�L�X�g�X�s�[�h
	int32_t textSpeed_;
	//�e�L�X�g��
	int32_t textCount_;
	//�e�L�X�g�ǉ�����
	int32_t textAddTimer_;

	//�Q�[���V�[���p�ϐ�
	//�v���C���[���S�t���O
	bool isDead_;
	//�N���A�V�[���t���O
	bool isClear_;
	//�G�l�~�[�ǂݍ��ݑҋ@�t���O
	bool isWait_;
	//���b�Z�[�W�f�[�^�ǂݍ��ݑҋ@�t���O
	bool isMessageWait_;
	//���b�Z�[�W�f�[�^�o�͊����t���O
	bool isTextDrawComplete_;
	//�v���C���[���S�����o�p�t���O
	bool isPlayerDead_;
	//�|�[�Y�t���O
	bool isPause_;
	//�^�C�g����ʕύX�t���O
	bool isTitleBack_;
	//���b�Z�[�W�E�B���h�E�I�[�v���t���O
	bool isTextWindowOpen_;
	//���X�^�[�g�t���O
	bool isRestart_;
	//�`���[�g���A�������t���O
	bool isMoveUp_;
	bool isMoveDown_;
	bool isMoveLeft_;
	bool isMoveRight_;
	bool isShot_;
	bool isBombShot_;
	//�`���[�g���A���A�C�R���A���t�@�l
	float how_to_up_alpha_;
	float how_to_down_alpha_;
	float how_to_left_alpha_;
	float how_to_right_alpha_;
	float how_to_shot_alpha_;
	float how_to_bomb_alpha_;
	//�G�l�~�[�ǂݍ��ݑҋ@����
	int32_t waitTimer_;
	//���b�Z�[�W�f�[�^�ǂݍ��ݑҋ@����
	int32_t waitMessageTimer_;
	//�N���A���o�p����
	int32_t clearTimer_;
	//�E�B���h�E������
	int32_t closeWindowTimer_;
	//�E�B���h�E�������
	int32_t openWindowTimer_;
	//�G�l�~�[�f�[�^�i�[�p������
	std::stringstream enemyData_;
	//���b�Z�[�W�f�[�^�i�[�p������
	std::stringstream textData_;
	//���b�Z�[�W���e�o�͗p������
	std::wstring drawMessage_;
	//���b�Z�[�W���e�i�[������
	std::wstring message_;
	//���[���J�����p�X�v���C���w��_�i�[�R���e�i
	std::vector<Vector3> points_;
	//���[���J�����p�J������]�p�x�i�[�R���e�i
	std::vector<Vector3> cameraRots_;
	//���[���J�����p�J�����ړ����Ԋi�[�R���e�i
	std::vector<float> cameraMoveTimes_;
	//�X�R�A
	int32_t score_;
	//��O���t�B�b�N�A�j���[�V�����^�C�}�[
	int32_t faceAnimeTimer_;
	//��O���t�B�b�N�A�j���[�V�����ԍ�
	int32_t faceAnimeCount_;
	//��O���t�B�b�N�^�C�v
	FaceGraphics faceType_;
	//�X���[���o�p�^�C�}�[
	int32_t delayTimer_;
	//�|�X�g�G�t�F�N�g�ԍ�
	PostEffect::PostEffectNo postEffectNo_;
};
