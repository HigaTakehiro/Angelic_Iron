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
private: //静的メンバ変数
	//デバックテキスト用テクスチャ番号
	static const int debugTextNumber = 0;

public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Sound* sound);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// エネミーデータの読み込み
	/// </summary>
	void LoadEnemyData();

	/// <summary>
	/// 読み込んだエネミーデータの更新
	/// </summary>
	void EnemyDataUpdate();

	/// <summary>
	/// スプライン曲線のテスト
	/// </summary>
	/// <param name="points">ベクター型の通るポイント</param>
	/// <param name="startIndex">最初の頂点</param>
	/// <param name="t">時間</param>
	/// <returns>位置</returns>
	Vector3 testSpline(const std::vector<Vector3>& points, const int& startIndex, const float& t);

private: //メンバ関数

	/// <summary>
	/// リセット処理
	/// </summary>
	void Reset();

private: //メンバ変数
	DirectXCommon* dxCommon = nullptr;
	KeyInput* input = nullptr;
	WinApp* winApp = nullptr;
	DebugText debugText;
	Sound* sound = nullptr;
	Camera* camera = nullptr;
	MapChip* mapchip = nullptr;

	//ゲームオブジェクト & スプライト
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

	//マップチップ用変数
	int** map1_a = nullptr;
	int** map1_b = nullptr;
	std::vector<Object3d*> objects;
	std::vector<Object3d*> objects2;

	//FBX用変数
	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;

	//ゲームシーン用変数
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

