#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "ImageManager.h"
#include "KeyInput.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "MouseInput.h"
#include "Button.h"
#include "LightGroup.h"

class GameOverScene : public BaseScene
{
public:

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
	//ScoreNumber JudgeDigitNumber(int32_t score, int32_t digit);

	/// <summary>
	/// シーン切り替え処理
	/// </summary>
	void SceneChange();

private: //静的メンバ変数
	static const int32_t waitTime = 60;

private: //メンバ変数

	PostEffect* postEffect_ = nullptr; //ポストエフェクトクラス
	Sprite* score_ = nullptr; //スコア画像
	Sprite* scoreNumbers_[6] = {}; ///スコア用連番数字画像
	Button* titleBack_ = nullptr;
	Button* restart_ = nullptr;

	PostEffect::PostEffectNo postEffectNo_; //ポストエフェクト番号
	//ライト
	LightGroup* light_ = nullptr;

	float scoreRollTimer_;
	DirectX::XMFLOAT2 scoreRollPos_[6] = {};
	DirectX::XMFLOAT2 mousePos_;

	Object3d* resultPlayer_ = nullptr;
	Object3d* ground_ = nullptr;
	Object3d* celetialSphere_ = nullptr;
	Camera* camera_ = nullptr;

	Vector3 playerRot_;
	Vector3 playerPos_;
	Vector3 playerScale_;

	Vector3 groundPos_;
	Vector3 groundScale_;

	Vector3 cameraPos_;
	Vector3 cameraTargetPos_;

	bool isTitleBack_;
	bool isRestart_;
	bool isSelectedButton_;
	bool isButtonSelectTiming_;

	int32_t waitTimer_;
};

