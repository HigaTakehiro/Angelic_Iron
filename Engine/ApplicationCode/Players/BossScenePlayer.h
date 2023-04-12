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
	void Initialize(Camera* camera);
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
	/// HP取得
	/// </summary>
	/// <returns>HP</returns>
	int32_t GetHPCount() { return hpCount; }
	/// <summary>
	/// ダメージフラグ取得
	/// </summary>
	/// <returns>ダメージフラグ</returns>
	bool GetIsDamage() { return isDamage; }
	/// <summary>
	/// 死亡フラグ取得
	/// </summary>
	/// <returns>死亡フラグ</returns>
	bool GetIsDead() { return isDead; }
	/// <summary>
	/// ダッシュフラグ取得
	/// </summary>
	/// <returns>ダッシュフラグ</returns>
	bool GetIsDash() { return isDash; }
	/// <summary>
	/// 左ダッシュフラグ取得
	/// </summary>
	/// <returns>左ダッシュフラグ</returns>
	bool GetIsLeftDash() { return isLeftDash; }
	/// <summary>
	/// 右ダッシュフラグ取得
	/// </summary>
	/// <returns>右ダッシュフラグ</returns>
	bool GetIsRightDash() { return isRightDash; }
	/// <summary>
	/// アングル取得
	/// </summary>
	/// <returns>アングル</returns>
	float GetAngle() { return cameraAngle; }
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
	/// <summary>
	/// ヒット時コールバック関数
	/// </summary>
	void OnCollision();
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
	/// <summary>
	/// ダメージエフェクト
	/// </summary>
	void DamageEffect();
	/// <summary>
	/// 死亡演出
	/// </summary>
	void DeadPerformance();

private: //静的メンバ変数
	//回転時間
	static const int32_t rotationTime;
	//ダッシュ時間
	static const int32_t dashTime;
	//弾発射間隔
	static const int32_t shotCoolTime;
	//最大残弾数
	static const int32_t maxBulletCount = 16;
	//最大HP
	static const int32_t maxHp = 3;
	//リロード時間
	static const int32_t reloadTime;
	//最大ブースト回数
	static const int32_t maxBoostCount = 3;
	//ブースト回復時間
	static const float boostReloadTime;
	//ダメージ時間
	static const int32_t damageTime;
	//死亡タイム
	static const int32_t deadTime;

private: //メンバ変数

	//3Dオブジェクト
	//プレイヤー
	Object3d* player;
	Object3d* gun;

	//2Dスプライト
	//レティクル
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
	int32_t bulletCount;
	//HP
	int32_t hpCount;
	//リロードフラグ
	bool isReload;
	//ブースト回復フラグ
	bool isBoostReload;
	//ブースト回復時間
	float boostReloadTimer;
	//ブースト数
	int32_t boostCount;
	//リロード時間
	int32_t reloadTimer;
	//レティクル座標
	DirectX::XMFLOAT2 aimPos;
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
	//ダメージフラグ
	bool isDamage;
	//ダメージタイマー
	int32_t damageTimer;
	//死亡タイマー
	int32_t deadTimer;
	//死亡フラグ
	bool isDead;
};