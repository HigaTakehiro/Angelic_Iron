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

private: //メンバ関数
	/// <summary>
	/// シーン切り替え処理
	/// </summary>
	void SceneChange();

private: //メンバ変数

	PostEffect* postEffect_ = nullptr; //ポストエフェクトクラス
	Sprite* score_ = nullptr; //スコア画像
	Sprite* scoreNumbers_[6] = {}; ///スコア用連番数字画像
	Sprite* titleBack_ = nullptr;

	LightGroup* light_ = nullptr;

	DirectX::XMFLOAT2 mousePos_;
	DirectX::XMFLOAT2 titleBackSize_;
	float titleBackAlpha_;

	PostEffect::PostEffectNo postEffectNo_; //ポストエフェクト番号

	float scoreRollTimer_;
	DirectX::XMFLOAT2 scoreRollPos_[6] = {};

	Object3d* resultPlayer_ = nullptr;
	Object3d* ground_ = nullptr;
	Object3d* celetialSphere_ = nullptr;
	Object3d* gun_ = nullptr;
	Camera* camera_ = nullptr;

	Vector3 playerRot_;
	Vector3 playerPos_;
	Vector3 playerScale_;

	Vector3 groundPos_;
	Vector3 groundScale_;

	Vector3 cameraPos_;
	Vector3 cameraTargetPos_;
};

