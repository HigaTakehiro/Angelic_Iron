#pragma once
#include "GameScene.h"
#include "DirectXCommon.h"

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
		Result,
		None
	};

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// シーン切り替え
	/// </summary>
	void SceneChange(SceneName sceneName);

private: //メンバ変数
	DirectXCommon* dxCommon;
	GameScene* gameScene;

	int nowSceneNo = Title;
	int nextSceneNo = None;
};

