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
#include "TextDraw.h"
#include "BulletCase.h"
#include "JsonLoader.h"
#include "ScoreItem.h"
#include "BulletManager.h"
#include "Button.h"

class ScoreItem;

class RailScene : public BaseScene
{
private: //静的メンバ変数
	//デバックテキスト用テクスチャ番号
	static const int32_t debugTextNumber = 0;

private: //サブクラス
	enum class FaceGraphics {
		OPE_NORMALFACE,
		OPE_SURPRISEFACE,
		OPE_SMILEFACE
	};

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
	/// 読み込んだエネミーデータの更新
	/// </summary>
	void EnemyDataUpdate();

	/// <summary>
	/// レールカメラ指定点を外部ファイルから読み込み
	/// </summary>
	void LoadRailPoint(const std::string& filename);

	/// <summary>
	/// 読み込んだテキストデータの更新
	/// </summary>
	void TextMessageUpdate();

	/// <summary>
	/// テキストデータの描画
	/// </summary>
	void TextMessageDraw();

	/// <summary>
	/// 敵オブジェクト取得
	/// </summary>
	/// <returns></returns>
	std::list<std::unique_ptr<BaseEnemy>>& GetEnemyObj() { return enemies_; }

private: //メンバ関数

	/// <summary>
	/// ロックオン距離か判定
	/// </summary>
	/// <param name="enemyPos">敵の画面上の位置</param>
	/// <param name="aimPos">マウスカーソルの位置</param>
	/// <returns>敵の位置にカーソルがあるかどうか</returns>
	bool IsTargetCheck(DirectX::XMFLOAT2 enemyPos, DirectX::XMFLOAT2 aimPos);

	/// <summary>
	/// スローにする更新処理
	/// </summary>
	void DelayUpdates();

	/// <summary>
	/// レールシューティングパートクリア演出
	/// </summary>
	void ClearPaformance();

	/// <summary>
	/// 当たり判定チェック
	/// </summary>
	void CollisionCheck();

	/// <summary>
	/// 敵関連の更新処理
	/// </summary>
	/// <param name="enemy"></param>
	void EnemyReactions(BaseEnemy* enemy);

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
	/// ボム攻撃演出
	/// </summary>
	void BombPerformance();

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
	//顔グラフィックアニメーション時間
	static const int32_t faceAnimeTime = 6;
	//テキストウィンドウ閉鎖時間
	static const int32_t closeWindowTime = 120;
	//テキストウィンドウ開放時間
	static const int32_t openWindowTime = 120;
	//ゲームオーバー条件HP
	static const int32_t noneHP = 0;
	//ボム攻撃時間
	static const int32_t bombTime = 60 * 5;

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
	//敵リスト
	std::list<std::unique_ptr<BaseEnemy>> enemies_;
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
	//スコアテキスト
	Sprite* scoreSprite_ = nullptr;
	//顔グラフィックウィンドウ
	Sprite* faceWindow_ = nullptr;
	//テキストウィンドウ
	Sprite* textWindow_ = nullptr;
	//オペレーター通常フェイス
	Sprite* opeNormal_[3] = {};
	//オペレーター驚愕フェイス
	Sprite* opeSurprise_[3] = {};
	//オペレーター笑顔フェイス
	Sprite* opeSmile_[3] = {};
	//スコア数字
	Sprite* scoreNumber_[6] = {};
	//ボム攻撃タイマー数字
	Sprite* bombTimerNumber_[3] = {};
	//チュートリアルアイコン
	Sprite* how_to_up_;
	Sprite* how_to_down_;
	Sprite* how_to_left_;
	Sprite* how_to_right_;
	Sprite* how_to_shot_;
	Sprite* how_to_bomb_;
	//テキストウィンドウサイズ
	DirectX::XMFLOAT2 textWindowSize_;
	//顔グラフィックウィンドウサイズ
	DirectX::XMFLOAT2 faceWindowSize_;
	//顔グラフィックサイズ
	DirectX::XMFLOAT2 faceGraphicSize_;

	//ライトオブジェクト
	LightGroup* light_ = nullptr;

	//テキスト描画用変数
	//DirectWriteテキスト描画クラス
	TextDraw* textDraw_ = nullptr;
	//テキストスピード
	int32_t textSpeed_;
	//テキスト数
	int32_t textCount_;
	//テキスト追加時間
	int32_t textAddTimer_;

	//ゲームシーン用変数
	//プレイヤー死亡フラグ
	bool isDead_;
	//クリアシーンフラグ
	bool isClear_;
	//エネミー読み込み待機フラグ
	bool isWait_;
	//メッセージデータ読み込み待機フラグ
	bool isMessageWait_;
	//メッセージデータ出力完了フラグ
	bool isTextDrawComplete_;
	//プレイヤー死亡時演出用フラグ
	bool isPlayerDead_;
	//ポーズフラグ
	bool isPause_;
	//タイトル画面変更フラグ
	bool isTitleBack_;
	//メッセージウィンドウオープンフラグ
	bool isTextWindowOpen_;
	//リスタートフラグ
	bool isRestart_;
	//チュートリアル完了フラグ
	bool isMoveUp_;
	bool isMoveDown_;
	bool isMoveLeft_;
	bool isMoveRight_;
	bool isShot_;
	bool isBombShot_;
	//チュートリアルアイコンアルファ値
	float how_to_up_alpha_;
	float how_to_down_alpha_;
	float how_to_left_alpha_;
	float how_to_right_alpha_;
	float how_to_shot_alpha_;
	float how_to_bomb_alpha_;
	//エネミー読み込み待機時間
	int32_t waitTimer_;
	//メッセージデータ読み込み待機時間
	int32_t waitMessageTimer_;
	//クリア演出用時間
	int32_t clearTimer_;
	//ウィンドウ閉鎖時間
	int32_t closeWindowTimer_;
	//ウィンドウ解放時間
	int32_t openWindowTimer_;
	//エネミーデータ格納用文字列
	std::stringstream enemyData_;
	//メッセージデータ格納用文字列
	std::stringstream textData_;
	//メッセージ内容出力用文字列
	std::wstring drawMessage_;
	//メッセージ内容格納文字列
	std::wstring message_;
	//レールカメラ用スプライン指定点格納コンテナ
	std::vector<Vector3> points_;
	//レールカメラ用カメラ回転角度格納コンテナ
	std::vector<Vector3> cameraRots_;
	//レールカメラ用カメラ移動時間格納コンテナ
	std::vector<float> cameraMoveTimes_;
	//スコア
	int32_t score_;
	//顔グラフィックアニメーションタイマー
	int32_t faceAnimeTimer_;
	//顔グラフィックアニメーション番号
	int32_t faceAnimeCount_;
	//顔グラフィックタイプ
	FaceGraphics faceType_;
	//スロー演出用タイマー
	int32_t delayTimer_;
	//ポストエフェクト番号
	PostEffect::PostEffectNo postEffectNo_;
};

