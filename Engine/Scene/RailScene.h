#pragma once
#include "KeyInput.h"//
#include "DirectXSetting.h"//
#include "Object3d.h"
#include "Model.h"
#include "Sprite.h"
#include "DebugText.h"
#include "Sound.h"//
#include "Camera.h"
#include "MapChip.h"
#include "SafeDelete.h"
#include "FbxLoader.h"
#include "FBXObject3d.h"
#include "MouseInput.h"
#include "PadInput.h"
#include "Player.h"
#include "Collision.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "ModelManager.h"
#include "RailCamera.h"
#include "ImageManager.h"
#include "PostEffect.h"
#include "Particle2d.h"
#include "Bomb.h"
#include <sstream>
#include <chrono>
#include <thread>
#include "BaseScene.h"
#include "SceneManager.h"
#include "BaseEnemy.h"
#include "StraightEnemy.h"
#include "HomingEnemy.h"
#include "LightGroup.h"
#include "ParticleManager.h"
#include "TextDraw.h"

using namespace DirectX;
using namespace Microsoft::WRL;
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
	/// エネミーデータの読み込み
	/// </summary>
	void LoadEnemyData(const std::string filename);

	/// <summary>
	/// 読み込んだエネミーデータの更新
	/// </summary>
	void EnemyDataUpdate();

	/// <summary>
	/// レールカメラ指定点を外部ファイルから読み込み
	/// </summary>
	void LoadRailPoint(const std::string filename);

	/// <summary>
	/// 会話データの読み込み
	/// </summary>
	/// <param name="fileName"></param>
	void LoadTextMessage(const std::string fileName);

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
	/// string型をwstring型に変換する(UTF-8)
	/// </summary>
	/// <param name="text">変換したいテキスト</param>
	/// <returns>wstring型のテキスト</returns>
	std::wstring StringToWstring(const std::string& text);

	/// <summary>
	/// ロックオン距離か判定
	/// </summary>
	/// <param name="enemyPos">敵の画面上の位置</param>
	/// <param name="aimPos">マウスカーソルの位置</param>
	/// <returns>敵の位置にカーソルがあるかどうか</returns>
	bool IsTargetCheck(XMFLOAT2 enemyPos, XMFLOAT2 aimPos);

private: //静的メンバ変数
	static const int32_t clearTime = 120;
	static const int32_t opeAnimeTime = 6;
	static const int32_t closeWindowTime = 120;
	static const int32_t openWindowTime = 120;

private: //メンバ変数
	WinApp* winApp = nullptr; //ウィンドウ設定クラス
	DebugText debugText; //デバッグテキスト表示用クラス
	Camera* camera = nullptr; //カメラクラス
	MapChip* mapchip = nullptr; //マップチップクラス
	RailCamera* railCamera = nullptr; //レールカメラクラス
	PostEffect* postEffect = nullptr; //ポストエフェクトクラス

	//ゲームオブジェクト & スプライト
	Player* player = nullptr; //プレイヤークラス
	std::list<std::unique_ptr<BaseEnemy>> enemies;
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets; //エネミーの弾リスト
	std::list<std::unique_ptr<PlayerBullet>> playerBullets; //プレイヤーの弾リスト
	std::list<std::unique_ptr<Particle2d>> particles2d; //2dパーティクルのリスト
	std::list<std::unique_ptr<Bomb>> bombs; //ボムの弾リスト
	std::list<std::unique_ptr<Object3d>> buildings; //ビルリスト
	ParticleManager* bombParticle;
	ParticleManager* enemyParticle;
	ParticleManager* bulletParticle;
	Sprite* background = nullptr; //背景画像
	Sprite* pause = nullptr;
	Sprite* titleBack = nullptr;
	Sprite* back = nullptr;
	Sprite* restart = nullptr;
	Sprite* scoreSprite = nullptr;
	Sprite* faceWindow = nullptr;
	Sprite* textWindow = nullptr;
	Sprite* opeNormal[3] = {};
	Sprite* opeSurprise[3] = {};
	Sprite* opeSmile[3] = {};
	Sprite* scoreNumber[6] = {};
	XMFLOAT2 titleBackSize;
	XMFLOAT2 backSize;
	XMFLOAT2 restartSize;
	XMFLOAT2 textWindowSize;
	XMFLOAT2 faceWindowSize;
	XMFLOAT2 operatorSize;

	Object3d* celetialSphere = nullptr; //天球オブジェクト
	Object3d* ground = nullptr; //地面オブジェクト
	Vector3 groundPos = { 0, 0, 0 }; //地面座標
	Vector3 groundScale = { 1, 1, 1 }; //地面の大きさ
	Vector3 spherePos = { 0, 0, 0 }; //天球座標
	Vector3 sphereScale = { 10, 10, 10 };  //天球の大きさ
	LightGroup* light = nullptr;

	//テキスト描画用変数
	TextDraw* textDraw = nullptr;
	int textSpeed;
	int textCount;
	int textAddTimer;

	//FBX用変数
	FBXObject3d* object1 = nullptr; //FBXテストオブジェクト

	//ゲームシーン用変数
	bool isDead; //プレイヤー死亡フラグ
	bool isClear; //クリアシーンフラグ
	bool isWait; //エネミー読み込み待機フラグ
	bool isMessageWait; //メッセージデータ読み込み待機フラグ
	bool isTextDraw; //メッセージデータ出力完了フラグ
	bool isPlayerDead; //プレイヤー死亡時演出用フラグ
	bool isPause; //ポーズフラグ
	bool isTitleBack; //タイトル画面変更フラグ
	bool isTextWindowOpen; //メッセージウィンドウオープンフラグ
	bool isRestart;
	int32_t waitTimer; //エネミー読み込み待機時間
	int32_t waitMessageTimer; //メッセージデータ読み込み待機時間
	int32_t clearTimer; //クリア演出用時間
	int32_t closeWindowTimer; //ウィンドウ閉鎖時間
	int32_t openWindowTimer; //ウィンドウ解放時間
	std::stringstream enemyData; //エネミーデータ格納用文字列
	std::stringstream textData; //メッセージデータ格納用文字列
	std::wstring drawMessage; //メッセージ内容出力用文字列
	std::wstring message; //メッセージ内容格納文字列
	std::vector<Vector3> points; //レールカメラ用スプライン指定点格納コンテナ
	std::chrono::steady_clock::time_point referenceCount; //スロー演出用参照時間

	int score;
	int32_t opeAnimeTimer;
	int opeAnimeCount;
	FaceGraphics faceType;

	PostEffect::PostEffectNo postEffectNo;
};

