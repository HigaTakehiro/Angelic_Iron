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
#include "ModelManager.h"
#include <sstream>

using namespace DirectX;
using namespace Microsoft::WRL;

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
	/// �X�v���C���Ȑ��̃e�X�g
	/// </summary>
	/// <param name="points">�x�N�^�[�^�̒ʂ�|�C���g</param>
	/// <param name="startIndex">�ŏ��̒��_</param>
	/// <param name="t">����</param>
	/// <returns>�ʒu</returns>
	Vector3 testSpline(const std::vector<Vector3>& points, const int& startIndex, const float& t);

private: //�����o�֐�

	/// <summary>
	/// ���Z�b�g����
	/// </summary>
	void Reset();

private: //�����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	KeyInput* input = nullptr;
	WinApp* winApp = nullptr;
	DebugText debugText;
	Sound* sound = nullptr;
	Camera* camera = nullptr;
	MapChip* mapchip = nullptr;

	//�Q�[���I�u�W�F�N�g & �X�v���C�g
	Player* player = nullptr;
	std::list<std::unique_ptr<Enemy>> enemies;
	Sprite* sprite = nullptr;
	Sprite* background = nullptr;
	Sprite* title = nullptr;
	Sprite* gameover = nullptr;
	Sprite* clear = nullptr;

	Model* celestialSphereModel = nullptr;
	Model* groundModel = nullptr;
	Object3d* celetialSphere = nullptr;
	Object3d* ground = nullptr;
	Vector3 groundPos = { 0, 0, 0 };
	Vector3 groundScale = { 1, 1, 1 };
	Vector3 spherePos = { 0, 0, 0 };
	Vector3 sphereScale = { 10, 10, 10 };

	//�}�b�v�`�b�v�p�ϐ�
	int** map1_a = nullptr;
	int** map1_b = nullptr;
	std::vector<Object3d*> objects;
	std::vector<Object3d*> objects2;

	//FBX�p�ϐ�
	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;

	//�Q�[���V�[���p�ϐ�
	float aimPosX;
	float aimPosY;
	bool isDead;
	bool isTitle;
	bool isClear;
	std::stringstream enemyData;

	//
	long long startCount = 1;
	long long nowCount = 0;
	long long elapsedCount = 0;

	Vector3 start = { 50.0f, 1.0f, 300.0f };
	Vector3 p2 = { 50.0f, -200.0f, 0.0f };
	Vector3 p3 = { 50.0f, 1.0f, -300.0f };
	Vector3 end = { -50.0f, 1.0f, 0.0f };
	std::vector<Vector3> points{ start, start, p2, p3, end, start, start };

	float maxTime = 15000.0f; //maxTime / 1000[s]
	float timeRate;
	int startIndex = 1;
	Vector3 cameraPos;
};

