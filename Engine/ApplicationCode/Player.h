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
#include "MatCalc.h"
#include "ModelManager.h"
#include "PlayerBullet.h"
#include "GameScene.h"
#include "Sound.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class GameScene;

class Player
{
public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Camera* camera, Sound* sound);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

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
	const XMFLOAT3 GetPlayerPos() { return playerWPos; }

	/// <summary>
	/// 3Dレティクルの位置取得
	/// </summary>
	/// <returns></returns>
	const Vector3 GetAimPos() { return aimPos3d; }

	/// <summary>
	/// 向き取得
	/// </summary>
	/// <returns>向き</returns>
	const XMFLOAT2 GetPlayerRot() { return aimPos; }

	/// <summary>
	/// プレイヤーオブジェクトの取得
	/// </summary>
	/// <returns>プレイヤーオブジェクト</returns>
	Object3d* GetPlayerObject() { return player; }

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
	/// <param name="gameScene">ゲームシーン</param>
	void SetGameScene(GameScene* gameScene) { this->gameScene = gameScene; }

	/// <summary>
	/// ダメージフラグ取得
	/// </summary>
	/// <returns>ダメージフラグ</returns>
	bool GetIsDamage() { return isDamage; }

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
	/// 3dレティクル更新処理
	/// </summary>
	void AimUpdate();

	/// <summary>
	/// ダメージエフェクト
	/// </summary>
	void DamageEffect();


private: //静的メンバ変数
	//最大残弾数
	static const int maxBulletCount = 16;
	//最大HP
	static const int maxHp = 3;
	//リロード時間
	static const int reloadTime = 60;
	//弾発射クールタイム
	static const int shotCoolTime = 10;
	//ダメージエフェクト発生時間
	static const int damageEffectTime = 20;

private: //メンバ変数
	Vector3 playerLPos = { 0, 0, 0 };
	Vector3 playerWPos = { 0, 0, 0 };
	Vector3 playerRot = { 0, 0, 0 };
	Vector3 playerScale = { 0, 0, 0 };

	Object3d* player = nullptr;
	Object3d* aim3d = nullptr;
	Sprite* aim = nullptr;
	Sprite* playerUI = nullptr;
	Sprite* hpUI[maxHp];
	Sprite* bulletUI[maxBulletCount];
	Sprite* reloadUI = nullptr;

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
	GameScene* gameScene;
	Sound* sound;

	//残弾数
	int bulletCount;
	//HP
	int hpCount;
	//リロード時間
	int reloadTimer;
	//弾発射クールタイム
	int shotCoolTimer;
	//リロードフラグ
	bool isReload = false;
	//ダメージエフェクト時間
	int damageEffectTimer;
	//ダメージエフェクト用フラグ
	bool isDamage = false;
};

