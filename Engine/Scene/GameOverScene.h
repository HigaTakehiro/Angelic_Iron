#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "ImageManager.h"
#include "KeyInput.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "MouseInput.h"

class GameOverScene : public BaseScene
{
public: //メンバ変数

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
	PostEffect* postEffect = nullptr;
	Sprite* gameover = nullptr; //ゲームオーバー画面画像
};

