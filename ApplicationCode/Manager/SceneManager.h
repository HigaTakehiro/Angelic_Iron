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
#include "TextDraw.h"

class SceneManager
{
public:
	SceneManager() = default;
	~SceneManager() = default;

public: //シーン管理番号
	enum class SceneName {
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
	static void AddScore(const int32_t score);

	/// <summary>
	/// スコアをセット
	/// </summary>
	/// <param name="score"></param>
	static void SetScore(const int32_t score);

	/// <summary>
	/// ボスシーンフラグをセット
	/// </summary>
	/// <param name="isBossScene">ボスシーンフラグ</param>
	static void SetIsBossScene(const bool isBossScene) { SceneManager::isBossScene_ = isBossScene; }

	/// <summary>
	/// ステージ番号取得
	/// </summary>
	/// <returns>ステージ番号</returns>
	static int32_t GetStageNo() { return stageNo_; }

	/// <summary>
	/// スコア取得
	/// </summary>
	/// <returns>スコア</returns>
	static int32_t GetScore() { return score_; }

	/// <summary>
	/// ボスシーンフラグを取得
	/// </summary>
	/// <returns>ボスシーンフラグ</returns>
	static bool GetIsBossScene() { return isBossScene_; }

private: //静的メンバ変数
	static BaseScene* nowScene_;
	static int32_t stageNo_;
	static int32_t score_;
	static bool isBossScene_;

private: //メンバ変数
	std::unique_ptr<TextDraw> textDraw_;
};