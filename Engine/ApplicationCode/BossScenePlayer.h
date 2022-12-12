#pragma once
#include "Object3d.h"
#include "ModelManager.h"
#include "Vector3.h"
#include "Camera.h"
#include "Sprite.h"
#include "ImageManager.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "MotionMath.h"
#include "SafeDelete.h"
#include "PlayerBullet.h"
#include "Easing.h"
#include "BossScene.h"
#include "Sound.h"

class BossScene;

class BossScenePlayer
{
public:
	BossScenePlayer() = default;
	~BossScenePlayer() = default;

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="sound">サウンド</param>
	void Initialize(Camera* camera, Sound* sound);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// スプライト描画
	/// </summary>
	void SpriteDraw();
	/// <summary>
	/// プレイヤーオブジェクト取得
	/// </summary>
	/// <returns></returns>
	Object3d* GetPlayerObj() { return player; }
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
	/// <summary>
	/// ボスシーンをセット
	/// </summary>
	/// <param name="bossScene">ボスシーン</param>
	void SetBossScene(BossScene* bossScene) { this->bossScene = bossScene; }

private: //メンバ関数
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// ダッシュ
	/// </summary>
	void Dash();
	/// <summary>
	/// ジャンプ
	/// </summary>
	void Jump();
	/// <summary>
	/// レティクル更新
	/// </summary>
	void AimUpdate();
	/// <summary>
	/// 弾発射
	/// </summary>
	void Shot(Vector3 mouse3dPos);

private: //静的メンバ変数
	//回転時間
	static const int32_t rotationTime;
	//ダッシュ時間
	static const int32_t dashTime;
	//弾発射間隔
	static const int32_t shotCoolTime;
	//最大残弾数
	static const int maxBulletCount = 16;
	//最大HP
	static const int maxHp = 3;
	//リロード時間
	static const int32_t reloadTime;
	//最大ブースト回数
	static const int maxBoostCount = 3;
	//ブースト回復時間
	static const float boostReloadTime;

private: //メンバ変数

	//3Dオブジェクト
	//プレイヤー
	Object3d* player;

	//2Dスプライト
	//レティクル
	Sprite* aim;
	Sprite* playerUI;
	Sprite* hpUI[maxHp];
	Sprite* bulletUI[maxBulletCount];
	Sprite* reloadUI;
	Sprite* boostUI[maxBoostCount];

	//カメラ
	Camera* camera;
	
	//ボスシーン
	BossScene* bossScene;
	//サウンドクラス
	Sound* sound;

	//ゲームシーン用変数
	//回転時間
	int32_t rotationTimer;
	//ダッシュフラグ
	bool isDash;
	bool isLeftDash;
	bool isRightDash;
	//ダッシュ時間
	int32_t dashTimer;
	//ダッシュ用初期アングル保存
	float initAngle;
	//ジャンプ上昇速度
	float jumpPower;
	//ジャンプフラグ
	bool isJump;
	//弾発射クールタイマー
	int32_t shotCoolTimer;
	//弾発射フラグ
	bool isShot;
	//弾数
	int bulletCount;
	//HP
	int hpCount;
	//リロードフラグ
	bool isReload;
	//ブースト回復フラグ
	bool isBoostReload;
	//ブースト回復時間
	float boostReloadTimer;
	//ブースト数
	int boostCount;
	//リロード時間
	int32_t reloadTimer;
	//レティクル座標
	XMFLOAT2 aimPos;
	//レティクル3D座標
	Vector3 aim3dPos;
	//ローカル座標
	Vector3 pos;
	//回転角
	Vector3 rot;
	//大きさ
	Vector3 scale;
	//プレイヤーワールド座標
	Vector3 playerWPos;
	//カメラアングル
	float cameraAngle;
	//カメラ座標
	Vector3 cameraPos;
};