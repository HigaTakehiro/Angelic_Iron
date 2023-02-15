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
	/// シーン変更フラグを取得する
	/// </summary>
	/// <returns></returns>
	bool GetIsSceneChange() { return isSceneChange; }

	/// <summary>
	/// シーン変更完了フラグを立てる
	/// </summary>
	/// <param name="isSceneChangeComplete"></param>
	void SetIsSceneChangeComplete(bool isSceneChangeComplete) { this->isSceneChangeComplete = isSceneChangeComplete; }

public: //静的メンバ変数
	//シーン切り替え時間
	static int32_t sceneChangeTimer;
	//シーン切り替え用スプライト
	static Sprite* sceneChangeEffects[10];
	//シーン切り替え用スプライト座標
	static DirectX::XMFLOAT2 sceneChangeEffectPos[10];
	//シーン切り替え開始フラグ
	static bool isSceneChangeStart;
	//シーン切り替えフラグ
	static bool isSceneChange;
	//シーン切り替え完了フラグ
	static bool isSceneChangeComplete;
};

