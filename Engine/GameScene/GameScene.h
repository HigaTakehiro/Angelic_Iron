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
	/// 敵弾を追加
	/// </summary>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet);

	/// <summary>
	/// プレイヤー弾を追加
	/// </summary>
	void AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet);

private: //メンバ関数

	/// <summary>
	/// リセット処理
	/// </summary>
	void Reset();

private: //メンバ変数
	DirectXCommon* dxCommon = nullptr; //DirectX初期設定クラス
	KeyInput* input = nullptr; //キーボード入力クラス
	WinApp* winApp = nullptr; //ウィンドウ設定クラス
	DebugText debugText; //デバッグテキスト表示用クラス
	Sound* sound = nullptr; //サウンドクラス
	Camera* camera = nullptr; //カメラクラス
	MapChip* mapchip = nullptr; //マップチップクラス
	RailCamera* railCamera = nullptr; //レールカメラクラス

	//ゲームオブジェクト & スプライト
	Player* player = nullptr; //プレイヤークラス
	std::list<std::unique_ptr<Enemy>> enemies; //エネミーリスト
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets; //エネミーの弾リスト
	std::list<std::unique_ptr<PlayerBullet>> playerBullets; //プレイヤーの弾リスト
	Sprite* background = nullptr; //背景画像
	Sprite* title = nullptr; //タイトル画面画像
	Sprite* gameover = nullptr; //ゲームオーバー画面画像
	Sprite* clear = nullptr; //クリア画面画像

	Model* celestialSphereModel = nullptr; //天球モデル
	Model* groundModel = nullptr; //地面モデル
	Object3d* celetialSphere = nullptr; //天球オブジェクト
	Object3d* ground = nullptr; //地面オブジェクト
	Vector3 groundPos = { 0, 0, 0 }; //地面座標
	Vector3 groundScale = { 1, 1, 1 }; //地面の大きさ
	Vector3 spherePos = { 0, 0, 0 }; //天球座標
	Vector3 sphereScale = { 10, 10, 10 };  //天球の大きさ

	//マップチップ用変数
	int** map1_a = nullptr; //マップチップのcsv保存用変数
	int** map1_b = nullptr; //マップチップのcsv保存用変数
	std::vector<Object3d*> objects; //マップチップオブジェクト格納コンテナ
	std::vector<Object3d*> objects2; //マップチップオブジェクト格納コンテナ

	//FBX用変数
	FBXModel* model1 = nullptr; //FBXテストモデル
	FBXObject3d* object1 = nullptr; //FBXテストオブジェクト

	//ゲームシーン用変数
	bool isDead; //プレイヤー死亡フラグ
	bool isTitle; //タイトルシーンフラグ
	bool isClear; //クリアシーンフラグ
	bool isWait; //エネミー読み込み待機フラグ
	int32_t waitTimer; //エネミー読み込み待機時間
	std::stringstream enemyData; //エネミーデータ格納用文字列

	const Vector3 start = { 50.0f, 1.0f, 300.0f }; //レールカメラ用スプライン指定点
	const Vector3 p2 = { 250.0f, 200.0f, 0.0f }; //レールカメラ用スプライン指定点
	const Vector3 p3 = { 50.0f, 200.0f, -300.0f }; //レールカメラ用スプライン指定点
	const Vector3 p4 = { -250.0f, 150.0f, -250.0f }; //レールカメラ用スプライン指定点
	const Vector3 p5 = { 0.0f, 5.0f, 50.0f };  //レールカメラ用スプライン指定点
	const Vector3 end = { -50.0f, 1.0f, 0.0f }; //レールカメラ用スプライン指定点
	std::vector<Vector3> points; //レールカメラ用スプライン指定点格納コンテナ

	const float maxTime = 15000.0f; //スプライン間補間時間 maxTime / 1000[s]
	Vector3 cameraPos; //カメラ座標
	Vector3 cameraRot; //カメラ回転角
};

