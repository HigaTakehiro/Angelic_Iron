#pragma once
#include "Object3d.h"
#include "ModelManager.h"
#include "Vector3.h"
#include "Camera.h"
#include "Sprite.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "MotionMath.h"
#include "SafeDelete.h"
#include "Easing.h"

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
	/// 終了処理
	/// </summary>
	void Finalize();

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

private: //静的メンバ変数
	static const int32_t rotationTime;
	static const int32_t dashTime;
	static const float gravity;

private: //メンバ変数
	//プレイヤー
	Object3d* player;
	//カメラ
	Camera* camera;
	//ローカル座標
	Vector3 pos;
	//回転角
	Vector3 rot;
	//大きさ
	Vector3 scale;
	//カメラアングル
	float cameraAngle;
	//カメラ座標
	Vector3 cameraPos;
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
};