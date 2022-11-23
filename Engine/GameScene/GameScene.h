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
#include "ImageManager.h"
#include "PostEffect.h"
#include "Particle2d.h"
#include "Bomb.h"
#include <sstream>
#include <chrono>
#include <thread>

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
	GameScene() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene() = default;

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
	/// レールカメラ指定点を外部ファイルから読み込み
	/// </summary>
	void LoadRailPoint();

	/// <summary>
	/// 敵弾を追加
	/// </summary>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet);

	/// <summary>
	/// プレイヤー弾を追加
	/// </summary>
	void AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet);

	/// <summary>
	/// ボムの弾を追加
	/// </summary>
	/// <param name="bomb"></param>
	void AddBomb(std::unique_ptr<Bomb> bomb);

	/// <summary>
	/// ターゲットされている敵の数取得
	/// </summary>
	int GetBombTarget();

	/// <summary>
	/// 敵オブジェクト取得
	/// </summary>
	/// <returns></returns>
	std::list<std::unique_ptr<Enemy>>& GetEnemyObj() { return enemies; }

private: //メンバ関数

	/// <summary>
	/// リセット処理
	/// </summary>
	void Reset();

	/// <summary>
	/// ロックオン距離か判定
	/// </summary>
	/// <param name="enemyPos">敵の画面上の位置</param>
	/// <param name="aimPos">マウスカーソルの位置</param>
	/// <returns>敵の位置にカーソルがあるかどうか</returns>
	bool IsTargetCheck(XMFLOAT2 enemyPos, XMFLOAT2 aimPos);

private: //静的メンバ変数
	static const int32_t clearTime = 120;

private: //メンバ変数
	DirectXCommon* dxCommon = nullptr; //DirectX初期設定クラス
	KeyInput* input = nullptr; //キーボード入力クラス
	WinApp* winApp = nullptr; //ウィンドウ設定クラス
	DebugText debugText; //デバッグテキスト表示用クラス
	Sound* sound = nullptr; //サウンドクラス
	Camera* camera = nullptr; //カメラクラス
	MapChip* mapchip = nullptr; //マップチップクラス
	RailCamera* railCamera = nullptr; //レールカメラクラス
	PostEffect* postEffect = nullptr; //ポストエフェクトクラス

	//ゲームオブジェクト & スプライト
	Player* player = nullptr; //プレイヤークラス
	std::list<std::unique_ptr<Enemy>> enemies; //エネミーリスト
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets; //エネミーの弾リスト
	std::list<std::unique_ptr<PlayerBullet>> playerBullets; //プレイヤーの弾リスト
	std::list<std::unique_ptr<Particle2d>> particles2d; //2dパーティクルのリスト
	std::list<std::unique_ptr<Bomb>> bombs; //ボムの弾リスト
	Sprite* background = nullptr; //背景画像
	Sprite* title = nullptr; //タイトル画面画像
	Sprite* gameover = nullptr; //ゲームオーバー画面画像
	Sprite* clear = nullptr; //クリア画面画像

	Object3d* celetialSphere = nullptr; //天球オブジェクト
	Object3d* ground = nullptr; //地面オブジェクト
	Vector3 groundPos = { 0, 0, 0 }; //地面座標
	Vector3 groundScale = { 1, 1, 1 }; //地面の大きさ
	Vector3 spherePos = { 0, 0, 0 }; //天球座標
	Vector3 sphereScale = { 10, 10, 10 };  //天球の大きさ

	//マップチップ用変数

	//FBX用変数
	FBXModel* model1 = nullptr; //FBXテストモデル
	FBXObject3d* object1 = nullptr; //FBXテストオブジェクト

	//ゲームシーン用変数
	bool isDead; //プレイヤー死亡フラグ
	bool isTitle; //タイトルシーンフラグ
	bool isClear; //クリアシーンフラグ
	bool isWait; //エネミー読み込み待機フラグ
	bool isPlayerDead; //プレイヤー死亡時演出用フラグ
	int32_t waitTimer; //エネミー読み込み待機時間
	int32_t clearTimer; //クリア演出用時間
	std::stringstream enemyData; //エネミーデータ格納用文字列

	std::vector<Vector3> points; //レールカメラ用スプライン指定点格納コンテナ

	std::chrono::steady_clock::time_point referenceCount; //スロー演出用参照時間
};

