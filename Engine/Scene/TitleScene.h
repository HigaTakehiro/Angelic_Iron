#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "ImageManager.h"

class TitleScene : public BaseScene
{
public: //メンバ関数
	/// <summary>
	/// 初期化関数
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Sound* sound);
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
	DirectXCommon* dxCommon;
	Sound* sound;

	Sprite* test;
};

