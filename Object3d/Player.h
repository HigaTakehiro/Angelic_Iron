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

using namespace DirectX;
using namespace Microsoft::WRL;

class Player
{
public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Camera* camera);

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
	const XMFLOAT3 GetPlayerPos() { return aimPos3d; }

	/// <summary>
	/// 向き取得
	/// </summary>
	/// <returns>向き</returns>
	//const XMFLOAT3 GetPlayerRot() { return  }

	/// <summary>
	/// プレイヤーオブジェクトの取得
	/// </summary>
	/// <returns>プレイヤーオブジェクト</returns>
	Object3d* GetPlayerObject() { return player; }

	/// <summary>
	/// 弾オブジェクトの取得
	/// </summary>
	/// <returns>弾オブジェクト</returns>
	Object3d* GetShotObject() { return shot; }

	/// <summary>
	/// リセット処理
	/// </summary>
	void Reset();

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
	/// 座標に行列を掛けて最後にw除算する
	/// </summary>
	/// <param name="vec">座標</param>
	/// <param name="mat">行列</param>
	/// <returns>計算結果</returns>
	XMVECTOR Wdivided(XMVECTOR vec, XMMATRIX mat);

private: //メンバ変数
	Vector3 playerLPos = { 0, 0, 0 };
	Vector3 playerWPos = { 0, 0, 0 };
	Vector3 playerRot = { 0, 0, 0 };
	Vector3 playerScale = { 0, 0, 0 };
	Vector3 shotPos = { 0, 0, 0 };
	Vector3 shotRot = { 0, 0, 0 };
	Vector3 shotScale = { 0, 0, 0 };

	Model* playerModel = nullptr;
	Model* shotModel = nullptr;
	Object3d* player = nullptr;
	Object3d* shot = nullptr;
	Object3d* aim3d = nullptr;
	Sprite* aim = nullptr;

	bool isShot = false;
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
};

