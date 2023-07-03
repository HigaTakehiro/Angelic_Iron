#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "MotionMath.h"
#include "BossScenePlayer.h"
#include "PlayerBullet.h"
#include "Sound.h"
#include "BaseBoss.h"
#include "FirstBoss.h"
#include "Particle2d.h"
#include "LightGroup.h"
#include "MessageWindow.h"
#include "BulletManager.h"
#include "Button.h"
#include <fstream>

class BossScenePlayer;
class BaseBoss;
class FirstBoss;

class BossScene : public BaseScene
{

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

	/// <summary>
	/// シーン切り替え処理
	/// </summary>
	void SceneChange();

private: //静的メンバ変数
	static const int32_t opeAnimeTime = 6;
	static const int32_t closeWindowTime = 120;
	static const int32_t openWindowTime = 120;

private: //メンバ変数

	//ビルリスト
	std::list<std::unique_ptr<Object3d>> buildings_;
	BulletManager* bulletManager_;
	//2Dパーティクルリスト
	std::list<std::unique_ptr<Particle2d>> particles2d_;
	//カメラ
	Camera* camera_ = nullptr;
	//サウンド
	Sound* sound_ = nullptr;
	//プレイヤー
	BossScenePlayer* player_ = nullptr;
	//地面
	Object3d* ground_ = nullptr;
	//天球
	Object3d* celetialSphere_ = nullptr;
	//ポストエフェクト
	PostEffect* postEffect_ = nullptr;
	PostEffect::PostEffectNo postEffectNo_;
	int32_t postEffectTime_;
	//ライト
	LightGroup* light_ = nullptr;

	Vector3 groundPos_ = { 0, 0, 0 }; //地面座標
	Vector3 groundScale_ = { 1, 1, 1 }; //地面の大きさ
	Vector3 spherePos_ = { 0, 0, 0 }; //天球座標
	Vector3 sphereScale_ = { 10, 10, 10 };  //天球の大きさ

	Sprite* pause_ = nullptr;
	Button* titleBack_ = nullptr;
	Button* back_ = nullptr;
	Sprite* scoreText_ = nullptr;
	Sprite* scoreNumber_[6] = {};
	//テキスト用変数
	Sprite* movieBar_[2] = {};
	DirectX::XMFLOAT2 movieBarPos_[2] = {};
	//メッセージウィンドウ
	MessageWindow* messageWindow_;

	int32_t movieTimer_; //ムービー時間

	Vector3 cameraPos_; //カメラ座標

	//BaseBoss* boss;
	FirstBoss* firstBoss_;

	//スコア
	int32_t score_;
	//タイトル画面バックフラグ
	bool isTitleBack_;
	//ポーズフラグ
	bool isPause_;
	//死亡フラグ
	bool isDead_;
};