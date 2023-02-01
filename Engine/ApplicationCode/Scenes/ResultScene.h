#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ImageManager.h"
#include "Easing.h"
#include "LightGroup.h"

class ResultScene : public BaseScene
{
public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dxCommon"></param>
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

	PostEffect* postEffect = nullptr; //ポストエフェクトクラス
	Sprite* score = nullptr; //スコア画像
	Sprite* scoreNumbers[6] = {}; ///スコア用連番数字画像
	Sprite* titleBack = nullptr;

	LightGroup* light = nullptr;

	DirectX::XMFLOAT2 mousePos;
	DirectX::XMFLOAT2 titleBackSize;
	float titleBackAlpha;

	PostEffect::PostEffectNo postEffectNo; //ポストエフェクト番号

	float scoreRollTimer;
	DirectX::XMFLOAT2 scoreRollPos[6] = {};

	Object3d* resultPlayer = nullptr;
	Object3d* ground = nullptr;
	Object3d* celetialSphere = nullptr;
	Object3d* gun = nullptr;
	Camera* camera = nullptr;

	Vector3 playerRot;
	Vector3 playerPos;
	Vector3 playerScale;

	Vector3 groundPos;
	Vector3 groundScale;

	Vector3 cameraPos;
	Vector3 cameraTargetPos;
};

