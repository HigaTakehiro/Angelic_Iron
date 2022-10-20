#pragma once
#include "KeyInput.h"//
#include "DirectXCommon.h"//
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
#include "Enemy.h"
#include "Collision.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "ModelManager.h"
#include "RailCamera.h"
#include <sstream>

using namespace DirectX;
using namespace Microsoft::WRL;
class Enemy;
class Player;

class GameScene
{
private: //�ÓI�����o�ϐ�
	//�f�o�b�N�e�L�X�g�p�e�N�X�`���ԍ�
	static const int debugTextNumber = 0;

public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Sound* sound);

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
	void LoadEnemyData();

	/// <summary>
	/// �ǂݍ��񂾃G�l�~�[�f�[�^�̍X�V
	/// </summary>
	void EnemyDataUpdate();

	/// <summary>
	/// �G�e��ǉ�
	/// </summary>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet);

	/// <summary>
	/// �v���C���[�e��ǉ�
	/// </summary>
	void AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet);

private: //�����o�֐�

	/// <summary>
	/// ���Z�b�g����
	/// </summary>
	void Reset();

private: //�����o�ϐ�
	DirectXCommon* dxCommon = nullptr; //DirectX�����ݒ�N���X
	KeyInput* input = nullptr; //�L�[�{�[�h���̓N���X
	WinApp* winApp = nullptr; //�E�B���h�E�ݒ�N���X
	DebugText debugText; //�f�o�b�O�e�L�X�g�\���p�N���X
	Sound* sound = nullptr; //�T�E���h�N���X
	Camera* camera = nullptr; //�J�����N���X
	MapChip* mapchip = nullptr; //�}�b�v�`�b�v�N���X
	RailCamera* railCamera = nullptr; //���[���J�����N���X

	//�Q�[���I�u�W�F�N�g & �X�v���C�g
	Player* player = nullptr; //�v���C���[�N���X
	std::list<std::unique_ptr<Enemy>> enemies; //�G�l�~�[���X�g
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets; //�G�l�~�[�̒e���X�g
	std::list<std::unique_ptr<PlayerBullet>> playerBullets; //�v���C���[�̒e���X�g
	Sprite* background = nullptr; //�w�i�摜
	Sprite* title = nullptr; //�^�C�g����ʉ摜
	Sprite* gameover = nullptr; //�Q�[���I�[�o�[��ʉ摜
	Sprite* clear = nullptr; //�N���A��ʉ摜

	Model* celestialSphereModel = nullptr; //�V�����f��
	Model* groundModel = nullptr; //�n�ʃ��f��
	Object3d* celetialSphere = nullptr; //�V���I�u�W�F�N�g
	Object3d* ground = nullptr; //�n�ʃI�u�W�F�N�g
	Vector3 groundPos = { 0, 0, 0 }; //�n�ʍ��W
	Vector3 groundScale = { 1, 1, 1 }; //�n�ʂ̑傫��
	Vector3 spherePos = { 0, 0, 0 }; //�V�����W
	Vector3 sphereScale = { 10, 10, 10 };  //�V���̑傫��

	//�}�b�v�`�b�v�p�ϐ�
	int** map1_a = nullptr; //�}�b�v�`�b�v��csv�ۑ��p�ϐ�
	int** map1_b = nullptr; //�}�b�v�`�b�v��csv�ۑ��p�ϐ�
	std::vector<Object3d*> objects; //�}�b�v�`�b�v�I�u�W�F�N�g�i�[�R���e�i
	std::vector<Object3d*> objects2; //�}�b�v�`�b�v�I�u�W�F�N�g�i�[�R���e�i

	//FBX�p�ϐ�
	FBXModel* model1 = nullptr; //FBX�e�X�g���f��
	FBXObject3d* object1 = nullptr; //FBX�e�X�g�I�u�W�F�N�g

	//�Q�[���V�[���p�ϐ�
	bool isDead; //�v���C���[���S�t���O
	bool isTitle; //�^�C�g���V�[���t���O
	bool isClear; //�N���A�V�[���t���O
	bool isWait; //�G�l�~�[�ǂݍ��ݑҋ@�t���O
	int32_t waitTimer; //�G�l�~�[�ǂݍ��ݑҋ@����
	std::stringstream enemyData; //�G�l�~�[�f�[�^�i�[�p������

	const Vector3 start = { 50.0f, 1.0f, 300.0f }; //���[���J�����p�X�v���C���w��_
	const Vector3 p2 = { 250.0f, 200.0f, 0.0f }; //���[���J�����p�X�v���C���w��_
	const Vector3 p3 = { 50.0f, 200.0f, -300.0f }; //���[���J�����p�X�v���C���w��_
	const Vector3 p4 = { -250.0f, 150.0f, -250.0f }; //���[���J�����p�X�v���C���w��_
	const Vector3 p5 = { 0.0f, 5.0f, 50.0f };  //���[���J�����p�X�v���C���w��_
	const Vector3 end = { -50.0f, 1.0f, 0.0f }; //���[���J�����p�X�v���C���w��_
	std::vector<Vector3> points; //���[���J�����p�X�v���C���w��_�i�[�R���e�i

	const float maxTime = 15000.0f; //�X�v���C���ԕ�Ԏ��� maxTime / 1000[s]
	Vector3 cameraPos; //�J�������W
	Vector3 cameraRot; //�J������]�p
};

