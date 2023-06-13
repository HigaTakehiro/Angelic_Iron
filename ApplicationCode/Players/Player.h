#pragma once
#include "KeyInput.h"
#include "Object3d.h"
#include "Model.h"
#include "MouseInput.h"
#include "PadInput.h"
#include "Sprite.h"
#include "Vector3.h"
#include "Camera.h"
#include "DebugText.h"
#include "WinApp.h"
#include "PlayerBullet.h"
#include <memory>
#include "Vector3.h"
#include "ModelManager.h"
#include "PlayerBullet.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "Bomb.h"
#include "BaseEnemy.h"
#include "RailScene.h"
#include "ParticleManager.h"
#include "BulletCase.h"
#include "BulletManager.h"
#include "KeyInputHandler.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class BaseEnemy;
class KeyInputHandler;

class Player
{
public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Camera* camera, float clearTime);

	/// <summary>
	/// プレイヤー
	/// </summary>
	/// <param name="isClear">クリアフラグ</param>
	/// <param name="clearTimer">経過時間</param>
	/// <param name="clearTime">クリア演出時間</param>
	void Update(bool isClear);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// スプライト描画処理
	/// </summary>
	void SpriteDraw();

	/// <summary>
	/// 3Dオブジェクト描画処理
	/// </summary>
	void ObjectDraw();

	/// <summary>
	/// 位置取得
	/// </summary>
	/// <returns>位置</returns>
	const XMFLOAT3 GetPlayerPos() { return playerLPos_; }

	/// <summary>
	/// 銃オブジェクト取得
	/// </summary>
	/// <returns>銃オブジェクト</returns>
	Object3d* GetGunObject() { return gun_; }

	/// <summary>
	/// 3Dレティクルの位置取得
	/// </summary>
	/// <returns></returns>
	const Vector3 Get3dAimPos() { return aimPos3d_; }

	/// <summary>
	/// レティクル位置取得
	/// </summary>
	/// <returns>向き</returns>
	const XMFLOAT2 GetAimPos() { return aimPos_; }

	/// <summary>
	/// プレイヤーオブジェクトの取得
	/// </summary>
	/// <returns>プレイヤーオブジェクト</returns>
	Object3d* GetPlayerObject() { return player_; }

	/// <summary>
	/// 残りHP取得
	/// </summary>
	/// <returns></returns>
	int32_t GetHPCount() { return hpCount_; }

	/// <summary>
	/// 死亡フラグ取得
	/// </summary>
	/// <returns>死亡フラグ</returns>
	bool GetIsDead() { return isDead_; }

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// リセット処理
	/// </summary>
	void Reset();

	/// <summary>
	/// ゲームシーンをセット
	/// </summary>
	/// <param name="RailScene">ゲームシーン</param>
	void SetRailScene(RailScene* RailScene) { railScene_ = RailScene; }

	/// <summary>
	/// 弾マネージャーをセット
	/// </summary>
	/// <param name="bulletManager">弾マネージャー</param>
	void SetBulletManager(BulletManager* bulletManager) { bulletManager_ = bulletManager; }

	/// <summary>
	/// クリア演出最終地点をセット
	/// </summary>
	/// <param name="clearPos">クリア演出最終地点</param>
	void SetClearPos(const Vector3 clearPos) { clearPos_ = clearPos; }

	/// <summary>
	/// 発射位置をセット
	/// </summary>
	/// <param name="shotDistance"></param>
	void SetShotDistance(const float shotDistance) { shotDistance_ = shotDistance; }

	/// <summary>
	/// プレイヤー座標にベクトルを加算
	/// </summary>
	/// <param name="vector">ベクトル</param>
	void AddPlayerVector(const Vector3 vector) { playerLPos_ += vector; }

	/// <summary>
	/// ダメージフラグ取得
	/// </summary>
	/// <returns>ダメージフラグ</returns>
	bool GetIsDamage() { return isDamage_; }

	/// <summary>
	/// ボムフラグ取得
	/// </summary>
	/// <returns>ボムフラグ</returns>
	bool GetIsBomb() { return isBomb_; }

	/// <summary>
	/// ボム攻撃タイマー取得
	/// </summary>
	/// <returns>ボム攻撃</returns>
	int32_t GetBombTimer() { return bombTimer_; }

	/// <summary>
	/// 発射フラグ取得
	/// </summary>
	/// <returns>発射フラグ</returns>
	bool GetIsShot() { return isShot_; }

	/// <summary>
	/// 通常攻撃処理
	/// </summary>
	void Shot();

	/// <summary>
	/// ボムモードに切り替える
	/// </summary>
	void SetBombMode();

	/// <summary>
	/// リロード処理
	/// </summary>
	void Reload();

	/// <summary>
	/// ボム攻撃処理
	/// </summary>
	void BombShot();

private: //メンバ関数

	/// <summary>
	/// 3dレティクル更新処理
	/// </summary>
	void AimUpdate();

	/// <summary>
	/// ダメージエフェクト
	/// </summary>
	void DamageEffect();

	/// <summary>
	/// 死亡演出
	/// </summary>
	void DeadPerformance();

	/// <summary>
	/// クリア演出
	/// </summary>
	/// <param name="clearTimer">クリア演出経過時間</param>
	/// <param name="clearTime">クリア演出時間</param>
	void ClearPerformance();

	/// <summary>
	/// スタート演出
	/// </summary>
	void StartPerformance();

	/// <summary>
	/// プレイヤー位置補正
	/// </summary>
	void PlayerPosCorrection();

	/// <summary>
	/// ボム攻撃時ベクトル方向判定
	/// </summary>
	/// <param name="enemyCount">ターゲットしている敵の数</param>
	/// <returns>ベクトル方向</returns>
	XMVECTOR BombVectorDirectionJudge(const int32_t enemyCount);

private: //静的メンバ変数
	//最大残弾数
	static const int32_t maxBulletCount = 16;
	//最大HP
	static const int32_t maxHp = 3;
	//リロード時間
	static const int32_t reloadTime = 60;
	//弾発射クールタイム
	static const int32_t shotCoolTime = 10;
	//ダメージエフェクト発生時間
	static const int32_t damageEffectTime = 40;
	//死亡時演出用時間
	static const int32_t deadTime = 120;
	//開始時演出用時間
	static const int32_t startTime = 60;
	//ボム攻撃タイマー
	static const int32_t bombTime = 60 * 5;
	//弾数がない状態
	static const int32_t noneBulletCount = 0;
	//移動速度
	static const float moveSpeed;

private: //メンバ変数
	Vector3 playerLPos_ = { 0, 0, 0 };
	Vector3 playerWPos_ = { 0, 0, 0 };
	Vector3 playerRot_ = { 0, 0, 0 };
	Vector3 playerScale_ = { 0, 0, 0 };
	Vector3 clearPos_ = {0.0f, 0.0f, 0.0f};

	Object3d* player_ = nullptr;
	Object3d* gun_ = nullptr;
	Sprite* playerUI_ = nullptr;
	Sprite* hpUI_[maxHp];
	Sprite* bulletUI_[maxBulletCount];
	Sprite* reloadUI_ = nullptr;
	Sprite* bomb_[3] = {};

	bool isShot_ = false;
	bool isDead_ = false;
	//ゲームシーン用変数
	XMFLOAT2 aimPos_;
	Vector3 oldShotPos_;
	Vector3 targetAimPos_;
	XMVECTOR positionRaticle_;
	XMMATRIX matViewPort_;
	XMMATRIX matViewProjection_;
	XMFLOAT3 aimPosMath_;

	Vector3 aimPos3d_;
	Camera* camera_;
	RailScene* railScene_;
	BulletManager* bulletManager_;

	//残弾数
	int32_t bulletCount_;
	//HP
	int32_t hpCount_;
	//リロード時間
	int32_t reloadTimer_;
	//弾発射クールタイム
	int32_t shotCoolTimer_;
	//ボム攻撃タイマー
	int32_t bombTimer_;
	//リロードフラグ
	bool isReload_ = false;
	//ダメージエフェクト時間
	int32_t damageEffectTimer_;
	//ダメージエフェクト用フラグ
	bool isDamage_ = false;
	//死亡時演出用時間
	int32_t deadTimer_;
	//イージング時間計測用配列
	float holdTimer_[4];
	//イージング用時間計測
	float returnTimer_;
	//クリア演出用時間計測
	float clearTimer_;
	//クリア時間
	float clearTime_;
	//スタート演出用時間計測
	int32_t startTimer_;
	//スタートフラグ
	bool isStart_;
	//ボムフラグ
	bool isBomb_;
	//ボム数
	int32_t bombCount_;
	//発射位置
	float shotDistance_;
	//コントローラー
	KeyInputHandler* controller_;
};