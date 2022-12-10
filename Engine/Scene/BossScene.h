#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "MotionMath.h"

class BossScene : public BaseScene
{
public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

private: //メンバ変数

	//ビルリスト
	std::list<std::unique_ptr<Object3d>> buildings;
	//カメラ
	Camera* camera = nullptr;
	//地面
	Object3d* ground = nullptr;
	//天球
	Object3d* celetialSphere = nullptr;
	//テストオブジェクト
	Object3d* test = nullptr;
	//ポストエフェクト
	PostEffect* postEffect = nullptr;
	PostEffect::PostEffectNo postEffectNo;

	Vector3 groundPos = { 0, 0, 0 }; //地面座標
	Vector3 groundScale = { 1, 1, 1 }; //地面の大きさ
	Vector3 spherePos = { 0, 0, 0 }; //天球座標
	Vector3 sphereScale = { 10, 10, 10 };  //天球の大きさ
	Vector3 cameraPos = { 0, -50.0f, 0 };
	float cameraAngle;
};

