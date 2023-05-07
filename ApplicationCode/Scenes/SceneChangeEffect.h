#pragma once
#include "Sprite.h"
#include "ImageManager.h"
#include <DirectXMath.h>

class SceneChangeEffect final
{
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneChangeEffect() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneChangeEffect() = default;
	/// <summary>
	/// コピーコンストラクタを禁止
	/// </summary>
	SceneChangeEffect(const SceneChangeEffect& obj) = delete;
	/// <summary>
	/// 代入演算子を禁止
	/// </summary>
	SceneChangeEffect& operator=(const SceneChangeEffect& obj) = delete;

public: //静的メンバ関数
	/// <summary>
	/// インスタンスを取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static SceneChangeEffect* GetIns();

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
	bool GetIsSceneChange() { return isSceneChange_; }

	/// <summary>
	/// シーン切り替え開始フラグを立てる
	/// </summary>
	/// <param name="isSceneChangeStart">シーン切り替え開始フラグ</param>
	void SetIsSceneChangeStart(bool isSceneChangeStart) { isSceneChangeStart_ = isSceneChangeStart; }

	/// <summary>
	/// シーン切り替え完了フラグを立てる
	/// </summary>
	/// <param name="isSceneChangeComplete">シーン切り替え完了フラグ</param>
	void SetIsSceneChangeComplete(bool isSceneChangeComplete) { isSceneChangeComplete_ = isSceneChangeComplete; }

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
	const static int32_t sceneChangeTime_;
	//シーン切り替えタイマー
	static int32_t sceneChangeTimer_;
	//シーン切り替え用スプライト
	static Sprite* sceneChangeEffects_[10];
	//シーン切り替え用スプライト座標
	static DirectX::XMFLOAT2 sceneChangeEffectsPos_[10];
	//シーン切り替え開始フラグ
	static bool isSceneChangeStart_;
	//シーン切り替えフラグ
	static bool isSceneChange_;
	//シーン切り替え完了フラグ
	static bool isSceneChangeComplete_;
};

