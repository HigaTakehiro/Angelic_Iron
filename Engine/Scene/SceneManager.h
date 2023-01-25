#pragma once

#include "RailScene.h"
#include "BaseScene.h"
#include "BossScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "GameOverScene.h"
#include "DirectXSetting.h"
#include "Sound.h"
#include "KeyInput.h"
#include "SafeDelete.h"

class SceneManager
{
public:
	SceneManager() = default;
	~SceneManager() = default;

public: //シーン管理番号
	enum SceneName {
		Title,
		Stage1_Rail,
		Stage1_Boss,
		Stage2_Rail,
		Stage2_Boss,
		Result,
		GameOver,
		None
	};

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

public: //静的メンバ関数

	/// <summary>
	/// 更新
	/// </summary>
	static void Update();

	/// <summary>
	/// 描画
	/// </summary>
	static void Draw();

	/// <summary>
	/// シーン切り替え
	/// </summary>
	static void SceneChange(SceneName scene);

	/// <summary>
	/// スコアを加算
	/// </summary>
	/// <param name="score">スコア</param>
	static void AddScore(const int score);

	/// <summary>
	/// スコアをセット
	/// </summary>
	/// <param name="score"></param>
	static void SetScore(const int score);

	/// <summary>
	/// ステージ番号取得
	/// </summary>
	/// <returns>ステージ番号</returns>
	static int GetStageNo() { return stageNo; }

	/// <summary>
	/// スコア取得
	/// </summary>
	/// <returns>スコア</returns>
	static int GetScore() { return score; }

private: //静的メンバ変数
	static BaseScene* nowScene;
	static int stageNo;
	static int score;
};