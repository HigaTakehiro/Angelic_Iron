#pragma once
#include "Sprite.h"
#include "ImageManager.h"
#include <DirectXMath.h>

class SceneChange
{
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneChange() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneChange() = default;
	/// <summary>
	/// コピーコンストラクタを禁止
	/// </summary>
	SceneChange(const SceneChange& obj) = delete;
	/// <summary>
	/// 代入演算子を禁止
	/// </summary>
	SceneChange& operator=(const SceneChange& obj) = delete;

public: //静的メンバ関数
	/// <summary>
	/// インスタンスを取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static SceneChange* GetIns();

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

	/// <summary>
	/// シーン切り替えフラグを取得する
	/// </summary>
	/// <returns>シーン切り替えフラグ</returns>
	bool GetIsSceneChange() { return isSceneChange; }

	/// <summary>
	/// シーン切り替え開始フラグを立てる
	/// </summary>
	/// <param name="isSceneChangeStart">シーン切り替え開始フラグ</param>
	void SetIsSceneChangeStart(bool isSceneChangeStart) { this->isSceneChangeStart = isSceneChangeStart; }

	/// <summary>
	/// シーン切り替え完了フラグを立てる
	/// </summary>
	/// <param name="isSceneChangeComplete">シーン切り替え完了フラグ</param>
	void SetIsSceneChangeComplete(bool isSceneChangeComplete) { this->isSceneChangeComplete = isSceneChangeComplete; }

private: //メンバ関数

	/// <summary>
	/// シーン切り替え演出
	/// </summary>
	void SceneChangePerformance();

	/// <summary>
	/// シーン切り替え完了演出
	/// </summary>
	void SceneChangeCompletePerformance();

private: //静的メンバ変数
	//シーン切り替え演出時間
	const static int32_t sceneChangeTime;
	//シーン切り替えタイマー
	static int32_t sceneChangeTimer;
	//シーン切り替え用スプライト
	static Sprite* sceneChangeEffects[10];
	//シーン切り替え用スプライト座標
	static DirectX::XMFLOAT2 sceneChangeEffectsPos[10];
	//シーン切り替え開始フラグ
	static bool isSceneChangeStart;
	//シーン切り替えフラグ
	static bool isSceneChange;
	//シーン切り替え完了フラグ
	static bool isSceneChangeComplete;
};

