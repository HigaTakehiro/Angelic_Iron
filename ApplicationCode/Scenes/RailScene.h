#pragma once
#include "Object3d.h"
#include "Sprite.h"
#include "DebugText.h"
#include "Camera.h"
#include "FBXObject3d.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "RailCamera.h"
#include "PostEffect.h"
#include "Particle2d.h"
#include "Bomb.h"
#include <sstream>
#include <thread>
#include "BaseScene.h"
#include "BaseEnemy.h"
#include "LightGroup.h"
#include "ParticleManager.h"
#include "BulletCase.h"
#include "JsonLoader.h"
#include "ScoreItem.h"
#include "BulletManager.h"
#include "Button.h"
#include "UIManager.h"
#include "EnemyManager.h"
#include "MessageWindow.h"
#include "RailTutorial.h"
#include "CollisionManager.h"

class ScoreItem;
class UIManager;
class EnemyManager;

class RailScene : public BaseScene
{
private: //静的メンバ変数

public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RailScene() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RailScene() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// 敵オブジェクト取得
	/// </summary>
	/// <returns></returns>
	std::list<std::unique_ptr<BaseEnemy>>& GetEnemyObj();

private: //メンバ関数

	/// <summary>
	/// スローにする更新処理
	/// </summary>
	void DelayUpdates();

	/// <summary>
	/// クリア演出
	/// </summary>
	void ClearPaformance();

	/// <summary>
	/// エフェクト発生処理
	/// </summary>
	void AddEffect();

	/// <summary>
	/// ポーズ中更新処理
	/// </summary>
	void Pause();

	/// <summary>
	/// チュートリアル処理
	/// </summary>
	void Tutorial();

	/// <summary>
	/// ボム攻撃エフェクト
	/// </summary>
	void BombHitEffect(Bomb* bomb);

private: //メンバ関数
	/// <summary>
	/// シーン切り替え処理
	/// </summary>
	void SceneChange();

private: //静的メンバ変数
	//クリア演出用時間
	static const int32_t clearTime = 120;
	//ゲームオーバー条件HP
	static const int32_t noneHP = 0;

private: //メンバ変数
	//ウィンドウ設定クラス
	WinApp* winApp_ = nullptr;
	//デバッグテキスト表示用クラス
	DebugText debugText_;
	//カメラクラス
	Camera* camera_ = nullptr;
	//レールカメラクラス
	RailCamera* railCamera_ = nullptr;
	//ポストエフェクトクラス
	PostEffect* postEffect_ = nullptr;
	
	//ゲームオブジェクト & スプライト
	//プレイヤークラス
	Player* player_ = nullptr;
	//弾マネージャー
	BulletManager* bulletManager_ = nullptr;
	// 敵管理マネージャー
	EnemyManager* enemyManager_ = nullptr;
	//メッセージウィンドウ
	MessageWindow* messageWindow_ = nullptr;
	//2dパーティクルのリスト
	std::list<std::unique_ptr<Particle2d>> particles2d_;
	//スコアアイテムリスト
	std::list<std::unique_ptr<ScoreItem>> scoreItems_;
	//jsonローダー
	std::unique_ptr<JsonLoader> jsonLoader_;
	//ボム用パーティクル
	ParticleManager* bombParticle_;
	//敵用パーティクル
	ParticleManager* enemyParticle_;
	//マズルフラッシュ用パーティクル
	ParticleManager* gunParticle_;
	//スラスター用パーティクル
	ParticleManager* thrusterParticle_;
	//ポーズテキスト
	Sprite* pause_ = nullptr;
	//タイトルバックボタン
	std::unique_ptr<Button> titleBackButton_;
	//ポーズ画面クローズボタン
	std::unique_ptr<Button> back_ = nullptr;
	//リスタートボタン
	std::unique_ptr<Button> restart_ = nullptr;
	//チュートリアル表示クラス
	RailTutorial* railTutorial_ = nullptr;

	//UIマネージャ
	UIManager* uiManager_ = nullptr;

	//ライトオブジェクト
	LightGroup* light_ = nullptr;

	//ゲームシーン用変数
	//プレイヤー死亡フラグ
	bool isDead_;
	//クリアシーンフラグ
	bool isClear_;
	//プレイヤー死亡時演出用フラグ
	bool isPlayerDead_;
	//ポーズフラグ
	bool isPause_;
	//タイトル画面変更フラグ
	bool isTitleBack_;
	//リスタートフラグ
	bool isRestart_;
	//クリア演出用時間
	int32_t clearTimer_;
	//スコア
	int32_t score_;
	//スロー演出用タイマー
	int32_t delayTimer_;
	//ポストエフェクト番号
	PostEffect::PostEffectNo postEffectNo_;
};

