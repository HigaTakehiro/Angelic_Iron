#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "ImageManager.h"
#include "KeyInput.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "MouseInput.h"
#include "LightGroup.h"

class GameOverScene : public BaseScene
{
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

private: //メンバ関数
	///// <summary>
	///// nの位の数字を判定する
	///// </summary>
	///// <param name="score">判定したいスコア</param>
	///// <param name="place">判定したいスコアの位</param>
	///// <returns></returns>
	//ScoreNumber JudgeDigitNumber(int score, int digit);

	/// <summary>
	/// シーン切り替え処理
	/// </summary>
	void SceneChange();

private: //メンバ変数

	PostEffect* postEffect = nullptr; //ポストエフェクトクラス
	Sprite* score = nullptr; //スコア画像
	Sprite* scoreNumbers[6] = {}; ///スコア用連番数字画像
	Sprite* titleBack = nullptr;
	Sprite* restart = nullptr;

	PostEffect::PostEffectNo postEffectNo; //ポストエフェクト番号
	//ライト
	LightGroup* light = nullptr;

	float scoreRollTimer;
	DirectX::XMFLOAT2 scoreRollPos[6] = {};
	DirectX::XMFLOAT2 titleBackSize;
	DirectX::XMFLOAT2 restartSize;
	DirectX::XMFLOAT2 mousePos;
	float titleBackAlpha;
	float restartAlpha;

	Object3d* resultPlayer = nullptr;
	Object3d* ground = nullptr;
	Object3d* celetialSphere = nullptr;
	Camera* camera = nullptr;

	Vector3 playerRot;
	Vector3 playerPos;
	Vector3 playerScale;

	Vector3 groundPos;
	Vector3 groundScale;

	Vector3 cameraPos;
	Vector3 cameraTargetPos;

	bool isTitleBack;
	bool isRestart;
	bool isSelectedButton;
};

