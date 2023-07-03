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
#include "BulletManager.h"
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
	Object3d* GetPlayerObj() { return player_; }
	/// <summary>
	/// HP取得
	/// </summary>
	/// <returns>HP</returns>
	int32_t GetHPCount() { return hpCount_; }
	/// <summary>
	/// ダメージフラグ取得
	/// </summary>
	/// <returns>ダメージフラグ</returns>
	bool GetIsDamage() { return isDamage_; }
	/// <summary>
	/// 死亡フラグ取得
	/// </summary>
	/// <returns>死亡フラグ</returns>
	bool GetIsDead() { return isDead_; }
	/// <summary>
	/// ダッシュフラグ取得
	/// </summary>
	/// <returns>ダッシュフラグ</returns>
	bool GetIsDash() { return isDash_; }
	/// <summary>
	/// 左ダッシュフラグ取得
	/// </summary>
	/// <returns>左ダッシュフラグ</returns>
	bool GetIsLeftDash() { return isLeftDash_; }
	/// <summary>
	/// 右ダッシュフラグ取得
	/// </summary>
	/// <returns>右ダッシュフラグ</returns>
	bool GetIsRightDash() { return isRightDash_; }
	/// <summary>
	/// アングル取得
	/// </summary>
	/// <returns>アングル</returns>
	float GetAngle() { return cameraAngle_; }
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
	void SetBossScene(BossScene* bossScene) { bossScene_ = bossScene; }

	/// <summary>
	/// 弾管理クラスをセット
	/// </summary>
	/// <param name="bulletManeger">弾管理クラス</param>
	void SetBulletManager(BulletManager* bulletManeger) { bulletManager_ = bulletManeger; }

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
	Object3d* player_;
	Object3d* gun_;

	//2Dスプライト
	//レティクル
	Sprite* playerUI_;
	Sprite* hpUI_[maxHp];
	Sprite* bulletUI_[maxBulletCount];
	Sprite* reloadUI_;
	Sprite* boostUI_[maxBoostCount];

	//カメラ
	Camera* camera_;
	
	//ボスシーン
	BossScene* bossScene_;
	//サウンドクラス
	Sound* sound_;
	//弾管理クラス
	BulletManager* bulletManager_;

	//ゲームシーン用変数
	//回転時間
	int32_t rotationTimer_;
	//ダッシュフラグ
	bool isDash_;
	bool isLeftDash_;
	bool isRightDash_;
	//ダッシュ時間
	int32_t dashTimer_;
	//ダッシュ用初期アングル保存
	float initAngle_;
	//ジャンプ上昇速度
	float jumpPower_;
	//ジャンプフラグ
	bool isJump_;
	//弾発射クールタイマー
	int32_t shotCoolTimer_;
	//弾発射フラグ
	bool isShot_;
	//弾数
	int32_t bulletCount_;
	//HP
	int32_t hpCount_;
	//リロードフラグ
	bool isReload_;
	//ブースト回復フラグ
	bool isBoostReload_;
	//ブースト回復時間
	float boostReloadTimer_;
	//ブースト数
	int32_t boostCount_;
	//リロード時間
	int32_t reloadTimer_;
	//レティクル座標
	DirectX::XMFLOAT2 aimPos_;
	//レティクル3D座標
	Vector3 aim3dPos_;
	//ローカル座標
	Vector3 pos_;
	//回転角
	Vector3 rot_;
	//大きさ
	Vector3 scale_;
	//プレイヤーワールド座標
	Vector3 playerWPos_;
	//カメラアングル
	float cameraAngle_;
	//カメラ座標
	Vector3 cameraPos_;
	//ダメージフラグ
	bool isDamage_;
	//ダメージタイマー
	int32_t damageTimer_;
	//死亡タイマー
	int32_t deadTimer_;
	//死亡フラグ
	bool isDead_;
};