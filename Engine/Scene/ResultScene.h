#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ImageManager.h"

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
	Sprite* clear = nullptr; //クリア画面画像

};

