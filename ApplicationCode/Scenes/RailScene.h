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
#include "BulletCase.h"
#include "JsonLoader.h"
#include "ScoreItem.h"
#include "BulletManager.h"
#include "Button.h"
#include "UIManager.h"
#include "EnemyManager.h"
#include "MessageWindow.h"
#include "RailTutorial.h"
#include "CollisionManager.h"

class ScoreItem;
class UIManager;
class EnemyManager;

class RailScene : public BaseScene
{
private: //�ÓI�����o�ϐ�

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
	/// �G�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns></returns>
	std::list<std::unique_ptr<BaseEnemy>>& GetEnemyObj();

private: //�����o�֐�

	/// <summary>
	/// �X���[�ɂ���X�V����
	/// </summary>
	void DelayUpdates();

	/// <summary>
	/// �N���A���o
	/// </summary>
	void ClearPaformance();

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
	//�Q�[���I�[�o�[����HP
	static const int32_t noneHP = 0;

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
	//�e�}�l�[�W���[
	BulletManager* bulletManager_ = nullptr;
	// �G�Ǘ��}�l�[�W���[
	EnemyManager* enemyManager_ = nullptr;
	//���b�Z�[�W�E�B���h�E
	MessageWindow* messageWindow_ = nullptr;
	//2d�p�[�e�B�N���̃��X�g
	std::list<std::unique_ptr<Particle2d>> particles2d_;
	//�X�R�A�A�C�e�����X�g
	std::list<std::unique_ptr<ScoreItem>> scoreItems_;
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
	std::unique_ptr<Button> titleBackButton_;
	//�|�[�Y��ʃN���[�Y�{�^��
	std::unique_ptr<Button> back_ = nullptr;
	//���X�^�[�g�{�^��
	std::unique_ptr<Button> restart_ = nullptr;
	//�`���[�g���A���\���N���X
	RailTutorial* railTutorial_ = nullptr;

	//UI�}�l�[�W��
	UIManager* uiManager_ = nullptr;

	//���C�g�I�u�W�F�N�g
	LightGroup* light_ = nullptr;

	//�Q�[���V�[���p�ϐ�
	//�v���C���[���S�t���O
	bool isDead_;
	//�N���A�V�[���t���O
	bool isClear_;
	//�v���C���[���S�����o�p�t���O
	bool isPlayerDead_;
	//�|�[�Y�t���O
	bool isPause_;
	//�^�C�g����ʕύX�t���O
	bool isTitleBack_;
	//���X�^�[�g�t���O
	bool isRestart_;
	//�N���A���o�p����
	int32_t clearTimer_;
	//�X�R�A
	int32_t score_;
	//�X���[���o�p�^�C�}�[
	int32_t delayTimer_;
	//�|�X�g�G�t�F�N�g�ԍ�
	PostEffect::PostEffectNo postEffectNo_;
};

