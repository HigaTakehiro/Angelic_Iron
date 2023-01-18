#pragma once
#include <DirectXMath.h>
#include "FbxLoader.h"
#include "FBXObject3d.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "Sprite.h"
#include "Easing.h"
#include "SafeDelete.h"

class BaseScene
{
public:
	//デストラクタ
	virtual ~BaseScene() {}

public:
	enum ScoreNumber {
		zero = 64 * 0,
		one = 64 * 1,
		two = 64 * 2,
		three = 64 * 3,
		four = 64 * 4,
		five = 64 * 5,
		six = 64 * 6,
		seven = 64 * 7,
		eight = 64 * 8,
		nine = 64 * 9
	};

public: //仮想関数
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Finalize() = 0;

public: //メンバ関数

	/// <summary>
	/// シーン切り替え用変数の初期化
	/// </summary>
	void SceneChangeInitialize();

	/// <summary>
	/// マウスがスプライトに触れているか(画像の中心が基準)
	/// </summary>
	/// <param name="mousePos">マウスの位置</param>
	/// <param name="spritePos">スプライトの位置</param>
	/// <param name="spriteWidth">スプライト横幅</param>
	/// <param name="spriteHeight">スプライト縦幅</param>
	/// <returns>マウスがスプライトを触れている</returns>
	bool IsMouseHitSprite(DirectX::XMFLOAT2 mousePos, DirectX::XMFLOAT2 spritePos, float spriteWidth, float spriteHeight);

	/// <summary>
	/// nの位の数字を判定する
	/// </summary>
	/// <param name="score">判定したいスコア</param>
	/// <param name="place">判定したいスコアの位</param>
	/// <returns></returns>
	ScoreNumber JudgeDigitNumber(int score, int digit);

	/// <summary>
	/// シーン切り替え用演出
	/// </summary>
	void SceneChangeEffect();

	/// <summary>
	/// シーン切り替え完了演出
	/// </summary>
	void SceneChangeCompleteEffect();

	/// <summary>
	/// シーン切り替え演出描画
	/// </summary>
	void SceneChangeEffectDraw();

	/// <summary>
	/// シーン切り替え完了フラグ
	/// </summary>
	/// <param name="isSceneChangeComplete">シーン切り替え完了フラグ</param>
	void SetSceneChangeComplete(const bool isSceneChangeComplete) { this->isSceneChangeComplete = isSceneChangeComplete; }

	/// <summary>
	/// シーン切り替え終了処理
	/// </summary>
	void SceneChangeFinalize();

protected: //静的メンバ変数
	//シーン切り替え演出用時間
	static int32_t sceneChangeTime;

	//シーン切り替え用スプライト
	static Sprite* sceneChangeEffects[10];
	//シーン切り替え用スプライト座標
	static XMFLOAT2 sceneChangeEffectsPos[10];
	//シーン切り替え演出用タイマー
	static int32_t sceneChangeTimer;
	//シーン切り替え開始フラグ
	static bool isSceneChangeStart;
	//シーン切り替えフラグ
	static bool isSceneChange;
	//シーン切り替え完了フラグ
	static bool isSceneChangeComplete;
};