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

class Player;

class RailScene : public BaseScene
{
private: //静的メンバ変数
	//デバックテキスト用テクスチャ番号
	static const int debugTextNumber = 0;

private: //サブクラス
	enum FaceGraphics {
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
	/// 敵弾を追加
	/// </summary>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet);

	/// <summary>
	/// プレイヤー弾を追加
	/// </summary>
	void AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet);

	/// <summary>
	/// 薬莢を追加
	/// </summary>
	/// <param name="bulletCase">薬莢</param>
	void AddBulletCase(std::unique_ptr<BulletCase> bulletCase);

	/// <summary>
	/// ボムの弾を追加
	/// </summary>
	/// <param name="bomb"></param>
	void AddBomb(std::unique_ptr<Bomb> bomb);

	/// <summary>
	/// 敵オブジェクト取得
	/// </summary>
	/// <returns></returns>
	std::list<std::unique_ptr<BaseEnemy>>& GetEnemyObj() { return enemies; }

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
	static const int noneHP = 0;

private: //メンバ変数
	//ウィンドウ設定クラス
	WinApp* winApp = nullptr;
	//デバッグテキスト表示用クラス
	DebugText debugText;
	//カメラクラス
	Camera* camera = nullptr;
	//レールカメラクラス
	RailCamera* railCamera = nullptr;
	//ポストエフェクトクラス
	PostEffect* postEffect = nullptr;

	//ゲームオブジェクト & スプライト
	//プレイヤークラス
	Player* player = nullptr;
	//敵リスト
	std::list<std::unique_ptr<BaseEnemy>> enemies;
	//エネミーの弾リスト
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets;
	//プレイヤーの弾リスト
	std::list<std::unique_ptr<PlayerBullet>> playerBullets;
	//2dパーティクルのリスト
	std::list<std::unique_ptr<Particle2d>> particles2d;
	//ボムの弾リスト
	std::list<std::unique_ptr<Bomb>> bombs;
	//薬莢リスト
	std::list<std::unique_ptr<BulletCase>> bulletCases;
	//ビルリスト
	std::list<std::unique_ptr<Object3d>> buildings;
	//ボム用パーティクル
	ParticleManager* bombParticle;
	//敵用パーティクル
	ParticleManager* enemyParticle;
	//マズルフラッシュ用パーティクル
	ParticleManager* gunParticle;
	//スラスター用パーティクル
	ParticleManager* thrusterParticle;
	//ポーズテキスト
	Sprite* pause = nullptr;
	//タイトルバックボタン
	Sprite* titleBack = nullptr;
	//ポーズ画面クローズボタン
	Sprite* back = nullptr;
	//リスタートボタン
	Sprite* restart = nullptr;
	//スコアテキスト
	Sprite* scoreSprite = nullptr;
	//顔グラフィックウィンドウ
	Sprite* faceWindow = nullptr;
	//テキストウィンドウ
	Sprite* textWindow = nullptr;
	//オペレーター通常フェイス
	Sprite* opeNormal[3] = {};
	//オペレーター驚愕フェイス
	Sprite* opeSurprise[3] = {};
	//オペレーター笑顔フェイス
	Sprite* opeSmile[3] = {};
	//スコア数字
	Sprite* scoreNumber[6] = {};
	//チュートリアルアイコン
	Sprite* how_to_up_;
	Sprite* how_to_down_;
	Sprite* how_to_left_;
	Sprite* how_to_right_;
	Sprite* how_to_shot_;
	//タイトルバックボタンサイズ
	DirectX::XMFLOAT2 titleBackSize;
	//ポーズ画面クローズボタンサイズ
	DirectX::XMFLOAT2 backSize;
	//リスタートボタンサイズ
	DirectX::XMFLOAT2 restartSize;
	//テキストウィンドウサイズ
	DirectX::XMFLOAT2 textWindowSize;
	//顔グラフィックウィンドウサイズ
	DirectX::XMFLOAT2 faceWindowSize;
	//顔グラフィックサイズ
	DirectX::XMFLOAT2 faceGraphicSize;

	//天球オブジェクト
	Object3d* celetialSphere = nullptr;
	//地面オブジェクト
	Object3d* ground = nullptr;
	//地面座標
	Vector3 groundPos = { 0, 0, 0 };
	//地面の大きさ
	Vector3 groundScale = { 1, 1, 1 };
	//天球座標
	Vector3 spherePos = { 0, 0, 0 };
	//天球の大きさ
	Vector3 sphereScale = { 10, 10, 10 };
	//ライトオブジェクト
	LightGroup* light = nullptr;

	//テキスト描画用変数
	//DirectWriteテキスト描画クラス
	TextDraw* textDraw = nullptr;
	//テキストスピード
	int textSpeed;
	//テキスト数
	int textCount;
	//テキスト追加時間
	int textAddTimer;

	//ゲームシーン用変数
	//プレイヤー死亡フラグ
	bool isDead;
	//クリアシーンフラグ
	bool isClear;
	//エネミー読み込み待機フラグ
	bool isWait;
	//メッセージデータ読み込み待機フラグ
	bool isMessageWait;
	//メッセージデータ出力完了フラグ
	bool isTextDrawComplete;
	//プレイヤー死亡時演出用フラグ
	bool isPlayerDead;
	//ポーズフラグ
	bool isPause;
	//タイトル画面変更フラグ
	bool isTitleBack;
	//メッセージウィンドウオープンフラグ
	bool isTextWindowOpen;
	//リスタートフラグ
	bool isRestart;
	//チュートリアル完了フラグ
	bool isMoveUp_;
	bool isMoveDown_;
	bool isMoveLeft_;
	bool isMoveRight_;
	bool isShot_;
	//チュートリアルアイコンアルファ値
	float how_to_up_alpha_;
	float how_to_down_alpha_;
	float how_to_left_alpha_;
	float how_to_right_alpha_;
	float how_to_shot_alpha_;
	//エネミー読み込み待機時間
	int32_t waitTimer;
	//メッセージデータ読み込み待機時間
	int32_t waitMessageTimer;
	//クリア演出用時間
	int32_t clearTimer;
	//ウィンドウ閉鎖時間
	int32_t closeWindowTimer;
	//ウィンドウ解放時間
	int32_t openWindowTimer;
	//エネミーデータ格納用文字列
	std::stringstream enemyData;
	//メッセージデータ格納用文字列
	std::stringstream textData;
	//メッセージ内容出力用文字列
	std::wstring drawMessage;
	//メッセージ内容格納文字列
	std::wstring message;
	//レールカメラ用スプライン指定点格納コンテナ
	std::vector<Vector3> points;
	//スコア
	int score;
	//顔グラフィックアニメーションタイマー
	int32_t faceAnimeTimer;
	//顔グラフィックアニメーション番号
	int faceAnimeCount;
	//顔グラフィックタイプ
	FaceGraphics faceType;
	//スロー演出用タイマー
	int32_t delayTimer;
	//ポストエフェクト番号
	PostEffect::PostEffectNo postEffectNo;
};

