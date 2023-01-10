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
#include "TextDraw.h"
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
	/// <summary>
	/// プレイヤー弾を追加
	/// </summary>
	void AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet);
	/// <summary>
	/// ボス弾を追加
	/// </summary>
	/// <param name="bossEnemy"></param>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> bosBullet);

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

private: //メンバ関数
	/// <summary>
	/// string型をwstring型に変換する(UTF-8)
	/// </summary>
	/// <param name="text">変換したいテキスト</param>
	/// <returns>wstring型のテキスト</returns>
	std::wstring StringToWstring(const std::string& text);

private: //静的メンバ変数
	static const int32_t opeAnimeTime = 6;
	static const int32_t closeWindowTime = 120;

private: //メンバ変数

	//ビルリスト
	std::list<std::unique_ptr<Object3d>> buildings;
	//プレイヤー弾リスト
	std::list<std::unique_ptr<PlayerBullet>> playerBullets;
	//ボス弾リスト
	std::list<std::unique_ptr<EnemyBullet>> bossBullets;
	//2Dパーティクルリスト
	std::list<std::unique_ptr<Particle2d>> particles2d;
	//カメラ
	Camera* camera = nullptr;
	//サウンド
	Sound* sound = nullptr;
	//プレイヤー
	BossScenePlayer* player = nullptr;
	//地面
	Object3d* ground = nullptr;
	//天球
	Object3d* celetialSphere = nullptr;
	//ポストエフェクト
	PostEffect* postEffect = nullptr;
	PostEffect::PostEffectNo postEffectNo;
	//ライト
	LightGroup* light = nullptr;

	Vector3 groundPos = { 0, 0, 0 }; //地面座標
	Vector3 groundScale = { 1, 1, 1 }; //地面の大きさ
	Vector3 spherePos = { 0, 0, 0 }; //天球座標
	Vector3 sphereScale = { 10, 10, 10 };  //天球の大きさ

	Sprite* pause = nullptr;
	Sprite* titleBack = nullptr;
	Sprite* back = nullptr;
	Sprite* scoreText = nullptr;
	Sprite* scoreNumber[6] = {};
	//テキスト用変数
	Sprite* faceWindow = nullptr;
	Sprite* textWindow = nullptr;
	Sprite* opeNormal[3] = {};
	XMFLOAT2 textWindowSize;
	XMFLOAT2 faceWindowSize;
	XMFLOAT2 operatorSize;

	TextDraw* textDraw = nullptr;
	int textSpeed;
	int textCount;
	int textAddTimer;

	int32_t closeWindowTimer; //ウィンドウ閉鎖時間

	bool isMessageWait; //メッセージデータ読み込み待機フラグ
	bool isMessageEnd; //メッセージ描画終了フラグ
	int32_t waitMessageTimer; //メッセージデータ読み込み待機時間
	bool isTextDraw; //メッセージデータ出力完了フラグ

	std::stringstream textData; //メッセージデータ格納用文字列
	std::wstring drawMessage; //メッセージ内容出力用文字列
	std::wstring message; //メッセージ内容格納文字列

	int32_t opeAnimeTimer;
	int opeAnimeCount;

	//BaseBoss* boss;
	FirstBoss* firstBoss;

	XMFLOAT2 titleBackSize;
	XMFLOAT2 backSize;
	//スコア
	int score;

	//ポーズフラグ
	bool isPause;
	//タイトルバックフラグ
	bool isTitleBack;
	//死亡フラグ
	bool isDead;
};

