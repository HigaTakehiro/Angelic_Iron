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

using namespace DirectX;
using namespace Microsoft::WRL;

class RailScene;
class BaseEnemy;

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
	const XMFLOAT3 GetPlayerPos() { return playerLPos; }

	/// <summary>
	/// 銃オブジェクト取得
	/// </summary>
	/// <returns>銃オブジェクト</returns>
	Object3d* GetGunObject() { return gun; }

	/// <summary>
	/// 3Dレティクルの位置取得
	/// </summary>
	/// <returns></returns>
	const Vector3 Get3dAimPos() { return aimPos3d; }

	/// <summary>
	/// レティクル位置取得
	/// </summary>
	/// <returns>向き</returns>
	const XMFLOAT2 GetAimPos() { return aimPos; }

	/// <summary>
	/// プレイヤーオブジェクトの取得
	/// </summary>
	/// <returns>プレイヤーオブジェクト</returns>
	Object3d* GetPlayerObject() { return player; }

	/// <summary>
	/// 残りHP取得
	/// </summary>
	/// <returns></returns>
	int32_t GetHPCount() { return hpCount; }

	/// <summary>
	/// 死亡フラグ取得
	/// </summary>
	/// <returns>死亡フラグ</returns>
	bool GetIsDead() { return isDead; }

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
	void SetRailScene(RailScene* RailScene) { this->railScene = RailScene; }

	/// <summary>
	/// ダメージフラグ取得
	/// </summary>
	/// <returns>ダメージフラグ</returns>
	bool GetIsDamage() { return isDamage; }

	/// <summary>
	/// ボムフラグ取得
	/// </summary>
	/// <returns>ボムフラグ</returns>
	bool GetIsBomb() { return isBomb; }

	/// <summary>
	/// ボム攻撃タイマー取得
	/// </summary>
	/// <returns>ボム攻撃</returns>
	int32_t GetBombTimer() { return bombTimer; }

	/// <summary>
	/// 発射フラグ取得
	/// </summary>
	/// <returns>発射フラグ</returns>
	bool GetIsShot() { return isShot; }

private: //メンバ関数
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// 通常攻撃処理
	/// </summary>
	void Shot();

	/// <summary>
	/// ボム攻撃処理
	/// </summary>
	void BombShot();

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

private: //静的メンバ変数
	//最大残弾数
	static const int32_t maxBulletCount = 16;
	//最大HP
	static const int32_t maxHp = 3;
	//リロード時間
	static const int32_t reloadTime = 20;
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

private: //メンバ変数
	Vector3 playerLPos = { 0, 0, 0 };
	Vector3 playerWPos = { 0, 0, 0 };
	Vector3 playerRot = { 0, 0, 0 };
	Vector3 playerScale = { 0, 0, 0 };

	Object3d* player = nullptr;
	Object3d* gun = nullptr;
	Sprite* playerUI = nullptr;
	Sprite* hpUI[maxHp];
	Sprite* bulletUI[maxBulletCount];
	Sprite* reloadUI = nullptr;
	Sprite* bomb[3] = {};

	bool isShot = false;
	bool isDead = false;
	//ゲームシーン用変数
	XMFLOAT2 aimPos;
	Vector3 oldShotPos;
	Vector3 targetAimPos;
	XMVECTOR positionRaticle;
	XMMATRIX matViewPort;
	XMMATRIX matViewProjection;
	XMFLOAT3 aimPosMath;

	Vector3 aimPos3d;
	Camera* camera;
	RailScene* railScene;

	//残弾数
	int32_t bulletCount;
	//HP
	int32_t hpCount;
	//リロード時間
	int32_t reloadTimer;
	//弾発射クールタイム
	int32_t shotCoolTimer;
	//ボム攻撃タイマー
	int32_t bombTimer;
	//リロードフラグ
	bool isReload = false;
	//ダメージエフェクト時間
	int32_t damageEffectTimer;
	//ダメージエフェクト用フラグ
	bool isDamage = false;
	//死亡時演出用時間
	int32_t deadTimer;
	//イージング時間計測用配列
	float holdTimer[4];
	//イージング用時間計測
	float returnTimer;
	//クリア演出用時間計測
	float clearTimer;
	//クリア時間
	float clearTime;
	//スタート演出用時間計測
	int32_t startTimer;
	//スタートフラグ
	bool isStart;
	//ボムフラグ
	bool isBomb;
	//ボム数
	int32_t bombCount;
};

