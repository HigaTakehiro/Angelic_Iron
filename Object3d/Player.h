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
	const XMFLOAT3 GetPlayerPos() { return aim3d->GetPosition(); }

	/// <summary>
	/// 向き取得
	/// </summary>
	/// <returns>向き</returns>
	const XMFLOAT3 GetPlayerRot() { return posFarMath; }

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

private: //メンバ変数
	Vector3 playerPos = { 0, 0, 0 };
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
	XMVECTOR posNear;
	XMVECTOR posFar;
	Vector3 posNearMath;
	Vector3 posFarMath;
	XMVECTOR positionRaticle;
	XMMATRIX matViewPort;
	XMMATRIX matViewProjection;
	XMFLOAT3 aimPosMath;

	//XMMATRIX matVPV;
	//XMMATRIX matInverseVPV;
	//Vector3 mouseDirection;
	XMVECTOR mouseDirection;
	Vector3 aimPos3d;
	Camera* camera;
};

